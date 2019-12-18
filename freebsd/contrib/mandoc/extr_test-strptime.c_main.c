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
struct tm {int tm_year; scalar_t__ tm_mon; int tm_mday; } ;

/* Variables and functions */
 char const* strptime (char const*,char*,struct tm*) ; 

int
main(void)
{
	struct tm tm;
	const char input[] = "2014-01-04";
	return ! (strptime(input, "%Y-%m-%d", &tm) == input + 10 &&
	    tm.tm_year == 114 && tm.tm_mon == 0 && tm.tm_mday == 4);
}