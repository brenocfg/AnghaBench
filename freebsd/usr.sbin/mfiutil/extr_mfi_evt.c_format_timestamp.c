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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tm ;
typedef  int time_t ;
struct tm {int tm_mday; int tm_year; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct tm*,int) ; 
 int /*<<< orphan*/  localtime (int*) ; 
 int mktime (struct tm*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
format_timestamp(uint32_t timestamp)
{
	static char buffer[32];
	static time_t base;
	time_t t;
	struct tm tm;

	if ((timestamp & 0xff000000) == 0xff000000) {
		snprintf(buffer, sizeof(buffer), "boot + %us", timestamp &
		    0x00ffffff);
		return (buffer);
	}

	if (base == 0) {
		/* Compute 00:00 Jan 1, 2000 offset. */
		bzero(&tm, sizeof(tm));
		tm.tm_mday = 1;
		tm.tm_year = (2000 - 1900);
		base = mktime(&tm);
	}
	if (base == -1) {
		snprintf(buffer, sizeof(buffer), "%us", timestamp);
		return (buffer);
	}
	t = base + timestamp;
	strftime(buffer, sizeof(buffer), "%+", localtime(&t));
	return (buffer);
}