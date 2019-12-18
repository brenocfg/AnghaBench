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
struct tm {int tm_year; int tm_yday; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ LDNS_DIV (scalar_t__,int) ; 
 scalar_t__ is_leap_year (int) ; 
 scalar_t__ leap_days (int,int) ; 

__attribute__((used)) static void
sldns_year_and_yday_from_days_since_epoch(int64_t days, struct tm *result)
{
	int year = 1970;
	int new_year;

	while (days < 0 || days >= (int64_t) (is_leap_year(year) ? 366 : 365)) {
		new_year = year + (int) LDNS_DIV(days, 365);
		days -= (new_year - year) * 365;
		days -= leap_days(year, new_year);
		year  = new_year;
	}
	result->tm_year = year;
	result->tm_yday = (int) days;
}