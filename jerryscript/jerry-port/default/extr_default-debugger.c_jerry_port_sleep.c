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
typedef  int useconds_t ;
typedef  scalar_t__ uint32_t ;
typedef  int time_t ;
struct timespec {int tv_sec; long tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (scalar_t__) ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

void jerry_port_sleep (uint32_t sleep_time) /**< milliseconds to sleep */
{
#ifdef WIN32
  Sleep (sleep_time);
#elif defined (HAVE_TIME_H)
  struct timespec sleep_timespec;
  sleep_timespec.tv_sec = (time_t) sleep_time / 1000;
  sleep_timespec.tv_nsec = ((long int) sleep_time % 1000) * 1000000L;

  nanosleep (&sleep_timespec, NULL);
#elif defined (HAVE_UNISTD_H)
  usleep ((useconds_t) sleep_time * 1000);
#else
  (void) sleep_time;
#endif /* HAVE_TIME_H */
}