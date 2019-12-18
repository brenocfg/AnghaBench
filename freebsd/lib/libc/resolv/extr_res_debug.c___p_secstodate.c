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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 struct tm* gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 char* p_secstodate_output ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
p_secstodate (u_long secs) {
	char *output = p_secstodate_output;
	time_t clock = secs;
	struct tm *time;
#ifdef HAVE_TIME_R
	struct tm res;

	time = gmtime_r(&clock, &res);
#else
	time = gmtime(&clock);
#endif
	time->tm_year += 1900;
	time->tm_mon += 1;
	sprintf(output, "%04d%02d%02d%02d%02d%02d",
		time->tm_year, time->tm_mon, time->tm_mday,
		time->tm_hour, time->tm_min, time->tm_sec);
	return (output);
}