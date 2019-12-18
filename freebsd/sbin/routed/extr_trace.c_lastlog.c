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
struct TYPE_3__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ftrace ; 
 TYPE_1__ lastlog_time ; 
 TYPE_1__ now ; 
 char* ts (scalar_t__) ; 

void
lastlog(void)
{
	if (lastlog_time.tv_sec != now.tv_sec
	    || lastlog_time.tv_usec != now.tv_usec) {
		(void)fprintf(ftrace, "-- %s --\n", ts(now.tv_sec));
		lastlog_time = now;
	}
}