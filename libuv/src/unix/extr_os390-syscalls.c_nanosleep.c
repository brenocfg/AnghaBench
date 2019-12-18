#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timespec {unsigned int tv_nsec; unsigned int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPX1CTW (unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int*,int*,int*) ; 
 int /*<<< orphan*/  BPX4CTW (unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int*,int*,int*) ; 
 unsigned int CW_CONDVAR ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 

int nanosleep(const struct timespec* req, struct timespec* rem) {
  unsigned nano;
  unsigned seconds;
  unsigned events;
  unsigned secrem;
  unsigned nanorem;
  int rv;
  int rc;
  int rsn;

  nano = (int)req->tv_nsec;
  seconds = req->tv_sec;
  events = CW_CONDVAR;

#if defined(_LP64)
  BPX4CTW(&seconds, &nano, &events, &secrem, &nanorem, &rv, &rc, &rsn);
#else
  BPX1CTW(&seconds, &nano, &events, &secrem, &nanorem, &rv, &rc, &rsn);
#endif

  assert(rv == -1 && errno == EAGAIN);

  if(rem != NULL) {
    rem->tv_nsec = nanorem;
    rem->tv_sec = secrem;
  }

  return 0;
}