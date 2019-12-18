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
 int SAVED_LONG_QUERIES ; 
 int /*<<< orphan*/ * last_long_query_buff ; 
 int /*<<< orphan*/ * last_long_query_found ; 
 int /*<<< orphan*/ * last_long_query_time ; 
 int /*<<< orphan*/ * last_long_query_utime ; 
 int long_query_buff_ptr ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stats_buff ; 

__attribute__((used)) static int prepare_long_query_stats (void) {
  char *tmp = stats_buff;
  int i;
  for (i = long_query_buff_ptr - 1; i >= 0; i--) {
    tmp += sprintf (tmp, "%.3lf %.6lf %d %.120s\n", last_long_query_utime[i], last_long_query_time[i], last_long_query_found[i], last_long_query_buff[i]);
  }
  for (i = SAVED_LONG_QUERIES - 1; i >= long_query_buff_ptr; i--) {
    tmp += sprintf (tmp, "%.3lf %.6lf %d %.120s\n", last_long_query_utime[i], last_long_query_time[i], last_long_query_found[i], last_long_query_buff[i]);
  }
  return tmp - stats_buff;
}