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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct mrb_time {int /*<<< orphan*/  timezone; int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_TIMEZONE_LOCAL ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  time_update_datetime (int /*<<< orphan*/ *,struct mrb_time*) ; 

__attribute__((used)) static struct mrb_time*
current_mrb_time(mrb_state *mrb)
{
  struct mrb_time *tm;

  tm = (struct mrb_time *)mrb_malloc(mrb, sizeof(*tm));
#if defined(TIME_UTC) && !defined(__ANDROID__)
  {
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
      mrb_free(mrb, tm);
      mrb_raise(mrb, E_RUNTIME_ERROR, "timespec_get() failed for unknown reasons");
    }
    tm->sec = ts.tv_sec;
    tm->usec = ts.tv_nsec / 1000;
  }
#elif defined(NO_GETTIMEOFDAY)
  {
    static time_t last_sec = 0, last_usec = 0;

    tm->sec  = time(NULL);
    if (tm->sec != last_sec) {
      last_sec = tm->sec;
      last_usec = 0;
    }
    else {
      /* add 1 usec to differentiate two times */
      last_usec += 1;
    }
    tm->usec = last_usec;
  }
#else
  {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    tm->sec = tv.tv_sec;
    tm->usec = tv.tv_usec;
  }
#endif
  tm->timezone = MRB_TIMEZONE_LOCAL;
  time_update_datetime(mrb, tm);

  return tm;
}