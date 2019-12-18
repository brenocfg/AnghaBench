#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hi; } ;
struct TYPE_6__ {TYPE_1__ d_s; } ;
typedef  TYPE_2__ vint64 ;
struct calendar {int year; int month; int monthday; int hour; int minute; int second; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 scalar_t__ ntpcal_ntp64_to_date (struct calendar*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static const char *
lstostr(
	const vint64 * ts)
{
	char *		buf;
	struct calendar tm;

	LIB_GETBUF(buf);

	if ( ! (ts->d_s.hi >= 0 && ntpcal_ntp64_to_date(&tm, ts) >= 0))
		snprintf(buf, LIB_BUFLENGTH, "%s", "9999-12-31T23:59:59Z");
	else
		snprintf(buf, LIB_BUFLENGTH, "%04d-%02d-%02dT%02d:%02d:%02dZ",
			tm.year, tm.month, tm.monthday,
			tm.hour, tm.minute, tm.second);

	return buf;
}