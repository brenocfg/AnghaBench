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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int snprintf (char*,size_t,char*,int,int,int,int,int,int) ; 

int dl_print_local_time (char *buf, int buf_size, time_t timestamp) {
  struct tm t;
  assert (localtime_r (&timestamp, &t));
  assert (buf_size > 0);
  return snprintf (buf, (size_t)buf_size, "[%4d-%02d-%02d %02d:%02d:%02d local] ", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}