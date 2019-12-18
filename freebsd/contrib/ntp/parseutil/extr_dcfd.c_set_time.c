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
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LPRINTF (char*,int /*<<< orphan*/ ) ; 
 int gettimeofday (struct timeval*,long) ; 
 scalar_t__ no_set ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pr_timeval (struct timeval*) ; 
 int settimeofday (struct timeval*,long) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeradd (struct timeval*,struct timeval*) ; 

__attribute__((used)) static void
set_time(
	 struct timeval *offset
	 )
{
	struct timeval the_time;

	if (no_set)
	    return;

	LPRINTF("set_time: %s ", pr_timeval(offset));
	syslog(LOG_NOTICE, "setting time (offset %s)", pr_timeval(offset));

	if (gettimeofday(&the_time, 0L) == -1)
	{
		perror("gettimeofday()");
	}
	else
	{
		timeradd(&the_time, offset);
		if (settimeofday(&the_time, 0L) == -1)
		{
			perror("settimeofday()");
		}
	}
}