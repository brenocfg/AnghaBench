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
struct tm {int tm_wday; int tm_year; int tm_yday; } ;

/* Variables and functions */
 int LDNS_MOD (int,int) ; 
 int leap_days (int,int) ; 

__attribute__((used)) static void
sldns_wday_from_year_and_yday(struct tm *result)
{
	result->tm_wday = 4 /* 1-1-1970 was a thursday */
			+ LDNS_MOD((result->tm_year - 1970), 7) * LDNS_MOD(365, 7)
			+ leap_days(1970, result->tm_year)
			+ result->tm_yday;
	result->tm_wday = LDNS_MOD(result->tm_wday, 7);
	if (result->tm_wday < 0) {
		result->tm_wday += 7;
	}
}