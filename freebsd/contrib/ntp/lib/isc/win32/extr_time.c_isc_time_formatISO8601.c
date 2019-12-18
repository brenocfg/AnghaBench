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
struct TYPE_3__ {int /*<<< orphan*/  absolute; } ;
typedef  TYPE_1__ isc_time_t ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 scalar_t__ FileTimeToSystemTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  GetTimeFormat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int TIME_FORCE24HOURFORMAT ; 
 int TIME_NOTIMEMARKER ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,char*,char*) ; 

void
isc_time_formatISO8601(const isc_time_t *t, char *buf, unsigned int len) {
	SYSTEMTIME st;
	char DateBuf[50];
	char TimeBuf[50];

/* strtime() format: "%Y-%m-%dT%H:%M:%SZ" */

	REQUIRE(len > 0);
	if (FileTimeToSystemTime(&t->absolute, &st)) {
		GetDateFormat(LOCALE_NEUTRAL, 0, &st, "yyyy-MM-dd",
			      DateBuf, 50);
		GetTimeFormat(LOCALE_NEUTRAL,
			      TIME_NOTIMEMARKER | TIME_FORCE24HOURFORMAT,
			      &st, "hh':'mm':'ss", TimeBuf, 50);
		snprintf(buf, len, "%s%sZ", DateBuf, TimeBuf);
	} else {
		buf[0] = 0;
	}
}