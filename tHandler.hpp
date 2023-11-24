#ifndef THANDLER_HPP_
#define THANDLER_HPP_

#include <thread>
using std::thread;
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <sys/prctl.h>

class tHandler
{
  public:
    void startThread(const string &threadName)
    {
      thread sampleThread = thread(&dispatch, this);
      tm[threadName] = sampleThread.native_handle();
      sampleThread.detach();
    }
    void stopThread(const string &threadName)
    {
      threadMap::const_iterator i = tm.find(threadName);
      if(i != tm.end())
      {
        pthread_cancel(i->second);
        tm.erase(threadName);
      }
    }
  private:
    typedef unordered_map<string, pthread_t> threadMap;
    threadMap tm;
};

#endif
