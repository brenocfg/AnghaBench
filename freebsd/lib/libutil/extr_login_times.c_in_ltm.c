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
typedef  scalar_t__ u_short ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_wday; int tm_hour; int tm_min; int tm_sec; } ;
struct TYPE_3__ {int lt_dow; scalar_t__ lt_start; scalar_t__ lt_end; } ;
typedef  TYPE_1__ login_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  mktime (struct tm*) ; 

int
in_ltm(const login_time_t *ltm, struct tm *tt, time_t *ends)
{
    int	    rc = 0;

    if (tt != NULL) {
	/* First, examine the day of the week */
	if ((u_char)(0x01 << tt->tm_wday) & ltm->lt_dow) {
	    /* Convert `current' time to minute of the day */
	    u_short	now = (u_short)((tt->tm_hour * 60) + tt->tm_min);

	    if (tt->tm_sec > 30)
		++now;
	    if (now >= ltm->lt_start && now < ltm->lt_end) {
		rc = 2;
		if (ends != NULL) {
		    /* If requested, return ending time for this period */
		    tt->tm_hour = (int)(ltm->lt_end / 60);
		    tt->tm_min  = (int)(ltm->lt_end % 60);
		    *ends = mktime(tt);
		}
	    }
	}
    }
    return (rc);
}