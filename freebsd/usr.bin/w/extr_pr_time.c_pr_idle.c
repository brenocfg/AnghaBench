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
typedef  int time_t ;

/* Variables and functions */
 int /*<<< orphan*/  xo_emit (char*,...) ; 

int
pr_idle(time_t idle)
{
	/* If idle more than 36 hours, print as a number of days. */
	if (idle >= 36 * 3600) {
		int days = idle / 86400;
		xo_emit(" {:idle/%dday%s} ", days, days > 1 ? "s" : " " );
		if (days >= 100)
			return (2);
		if (days >= 10)
			return (1);
	}

	/* If idle more than an hour, print as HH:MM. */
	else if (idle >= 3600)
		xo_emit(" {:idle/%2d:%02d/} ",
		    (int)(idle / 3600), (int)((idle % 3600) / 60));

	else if (idle / 60 == 0)
		xo_emit("     - ");

	/* Else print the minutes idle. */
	else
		xo_emit("    {:idle/%2d} ", (int)(idle / 60));

	return (0); /* not idle longer than 9 days */
}