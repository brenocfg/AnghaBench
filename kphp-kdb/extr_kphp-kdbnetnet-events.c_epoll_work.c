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

/* Variables and functions */
 double a_idle_quotient ; 
 double a_idle_time ; 
 int epoll_fetch_events (int) ; 
 int epoll_run_timers () ; 
 int epoll_runqueue () ; 
 scalar_t__ et_heap_size ; 
 scalar_t__ ev_heap_size ; 
 double get_utime_monotonic () ; 
 int now ; 
 scalar_t__ pending_signals ; 
 int time (int /*<<< orphan*/ ) ; 
 double tot_idle_time ; 

int epoll_work (int timeout) {
  int res;
  int timeout2 = 10000;
  if (ev_heap_size || et_heap_size) {
    now = time (0);
    get_utime_monotonic ();
    do {
      epoll_runqueue ();
      timeout2 = epoll_run_timers ();
    } while ((timeout2 <= 0 || ev_heap_size) && !pending_signals);
  }
  if (pending_signals) {
    return 0;
  }

  double epoll_wait_start = get_utime_monotonic ();

  res = epoll_fetch_events (timeout < timeout2 ? timeout : timeout2);

  double epoll_wait_time = get_utime_monotonic () - epoll_wait_start;
  tot_idle_time += epoll_wait_time;
  a_idle_time += epoll_wait_time;

  now = time (0);
  static int prev_now = 0;
  if (now > prev_now && now < prev_now + 60) {
    while (prev_now < now) {
      a_idle_time *= 100.0 / 101;
      a_idle_quotient = a_idle_quotient * (100.0/101) + 1;
      prev_now++;
    }
  } else {
    prev_now = now;
  }

  epoll_run_timers ();
  return epoll_runqueue();
}