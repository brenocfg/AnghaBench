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
typedef  int /*<<< orphan*/  u_int32 ;
typedef  scalar_t__ time_t ;
struct calendar {int year; int month; int monthday; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 scalar_t__ ntpcal_ntp_to_date (struct calendar*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 

char * fstostr(
	time_t	ntp_stamp
	)
{
	char *		buf;
	struct calendar tm;

	LIB_GETBUF(buf);
	if (ntpcal_ntp_to_date(&tm, (u_int32)ntp_stamp, NULL) < 0)
		snprintf(buf, LIB_BUFLENGTH, "ntpcal_ntp_to_date: %ld: range error",
			 (long)ntp_stamp);
	else
		snprintf(buf, LIB_BUFLENGTH, "%04d%02d%02d%02d%02d",
			 tm.year, tm.month, tm.monthday,
			 tm.hour, tm.minute);
	return buf;
}