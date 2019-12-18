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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int time_t ;

/* Variables and functions */
 int time (int /*<<< orphan*/ *) ; 
 int us_ticker_read () ; 

double
jerry_port_get_current_time (void)
{
  static uint64_t last_tick = 0;
  static time_t last_time = 0;
  static uint32_t skew = 0;

  uint64_t curr_tick = us_ticker_read (); /* The value is in microseconds. */
  time_t curr_time = time(NULL); /*  The value is in seconds. */
  double result = curr_time * 1000;

  /* The us_ticker_read () has an overflow for each UINT_MAX microseconds
   * (~71 mins). For each overflow event the ticker-based clock is about 33
   * milliseconds fast. Without a timer thread the milliseconds part of the
   * time can be corrected if the difference of two get_current_time calls
   * are within the mentioned 71 mins. Above that interval we can assume
   * that the milliseconds part of the time is negligibe.
   */
  if (curr_time - last_time > (time_t)(((uint32_t)-1) / 1000000)) {
    skew = 0;
  } else if (last_tick > curr_tick) {
    skew = (skew + 33) % 1000;
  }
  result += (curr_tick / 1000 - skew) % 1000;

  last_tick = curr_tick;
  last_time = curr_time;
  return result;
}