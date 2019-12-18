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
struct tm {int tm_year; int tm_mon; int tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  createdate (int,int,int) ; 
 size_t isleap (int) ; 
 int* monthdays ; 
 int** monthdaytab ; 

void
generatedates(struct tm *tp1, struct tm *tp2)
{
	int y1, m1, d1;
	int y2, m2, d2;
	int y, m, d;

	y1 = tp1->tm_year;
	m1 = tp1->tm_mon + 1;
	d1 = tp1->tm_mday;
	y2 = tp2->tm_year;
	m2 = tp2->tm_mon + 1;
	d2 = tp2->tm_mday;

	if (y1 == y2) {
		if (m1 == m2) {
			/* Same year, same month. Easy! */
			for (d = d1; d <= d2; d++)
				createdate(y1, m1, d);
			return;
		}
		/*
		 * Same year, different month.
		 * - Take the leftover days from m1
		 * - Take all days from <m1 .. m2>
		 * - Take the first days from m2
		 */
		monthdays = monthdaytab[isleap(y1)];
		for (d = d1; d <= monthdays[m1]; d++)
			createdate(y1, m1, d);
		for (m = m1 + 1; m < m2; m++)
			for (d = 1; d <= monthdays[m]; d++)
				createdate(y1, m, d);
		for (d = 1; d <= d2; d++)
			createdate(y1, m2, d);
		return;
	}
	/*
	 * Different year, different month.
	 * - Take the leftover days from y1-m1
	 * - Take all days from y1-<m1 .. 12]
	 * - Take all days from <y1 .. y2>
	 * - Take all days from y2-[1 .. m2>
	 * - Take the first days of y2-m2
	 */
	monthdays = monthdaytab[isleap(y1)];
	for (d = d1; d <= monthdays[m1]; d++)
		createdate(y1, m1, d);
	for (m = m1 + 1; m <= 12; m++)
		for (d = 1; d <= monthdays[m]; d++)
			createdate(y1, m, d);
	for (y = y1 + 1; y < y2; y++) {
		monthdays = monthdaytab[isleap(y)];
		for (m = 1; m <= 12; m++)
			for (d = 1; d <= monthdays[m]; d++)
				createdate(y, m, d);
	}
	monthdays = monthdaytab[isleap(y2)];
	for (m = 1; m < m2; m++)
		for (d = 1; d <= monthdays[m]; d++)
			createdate(y2, m, d);
	for (d = 1; d <= d2; d++)
		createdate(y2, m2, d);
}