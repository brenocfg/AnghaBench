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
typedef  scalar_t__ time_t ;
struct tm {scalar_t__ tm_year; scalar_t__ tm_mon; int /*<<< orphan*/  tm_mday; } ;

/* Variables and functions */
 scalar_t__ AD_RECOMPUTE_INTERVAL ; 
 int LOCAL_TIMEZONE_SHIFT_MINUTES ; 
 int /*<<< orphan*/  global_age_day ; 
 scalar_t__ global_age_month ; 
 scalar_t__ global_age_year ; 
 int /*<<< orphan*/  global_future_age_day ; 
 scalar_t__ global_future_age_month ; 
 scalar_t__ global_future_age_year ; 
 struct tm* gmtime (scalar_t__*) ; 
 scalar_t__ now ; 

__attribute__((used)) static void init_global_age_query_data (void) {
  struct tm *tmp;
  time_t nowd = now + LOCAL_TIMEZONE_SHIFT_MINUTES * 60;
  tmp = gmtime (&nowd);
  global_age_day = tmp->tm_mday;
  global_age_month = tmp->tm_mon + 1;
  global_age_year = tmp->tm_year + 1900;

  nowd += AD_RECOMPUTE_INTERVAL;
  tmp = gmtime (&nowd);
  global_future_age_day = tmp->tm_mday;
  global_future_age_month = tmp->tm_mon + 1;
  global_future_age_year = tmp->tm_year + 1900;
}