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

/* Variables and functions */

__attribute__((used)) static int
days_pmonth(int month, int year)
{
	static const int mtab[] = {31, 28, 31, 30, 31, 30, 31, 31,
	    30, 31, 30, 31};
	int ndays;

	ndays = mtab[month];

	if (month == 1) {
		/*
		 * We are usually called with a 'tm-year' value
		 * (ie, the value = the number of years past 1900).
		 */
		if (year < 1900)
			year += 1900;
		if (year % 4 == 0) {
			/*
			 * This is a leap year, as long as it is not a
			 * multiple of 100, or if it is a multiple of
			 * both 100 and 400.
			 */
			if (year % 100 != 0)
				ndays++;	/* not multiple of 100 */
			else if (year % 400 == 0)
				ndays++;	/* is multiple of 100 and 400 */
		}
	}
	return (ndays);
}