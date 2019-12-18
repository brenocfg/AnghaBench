#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_time_t ;
struct TYPE_3__ {int /*<<< orphan*/  tm_usec; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  TYPE_1__ apr_time_exp_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIMESTAMP_FORMAT ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_time_exp_gmt (TYPE_1__*,int /*<<< orphan*/ ) ; 

const char *
svn_time_to_cstring(apr_time_t when, apr_pool_t *pool)
{
  apr_time_exp_t exploded_time;

  /* We toss apr_status_t return value here -- for one thing, caller
     should pass in good information.  But also, where APR's own code
     calls these functions it tosses the return values, and
     furthermore their current implementations can only return success
     anyway. */

  /* We get the date in GMT now -- and expect the tm_gmtoff and
     tm_isdst to be not set. We also ignore the weekday and yearday,
     since those are not needed. */

  apr_time_exp_gmt(&exploded_time, when);

  /* It would be nice to use apr_strftime(), but APR doesn't give a
     way to convert back, so we wouldn't be able to share the format
     string between the writer and reader. */
  return apr_psprintf(pool,
                      TIMESTAMP_FORMAT,
                      exploded_time.tm_year + 1900,
                      exploded_time.tm_mon + 1,
                      exploded_time.tm_mday,
                      exploded_time.tm_hour,
                      exploded_time.tm_min,
                      exploded_time.tm_sec,
                      exploded_time.tm_usec);
}