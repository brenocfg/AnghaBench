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
struct tm {int tm_hour; scalar_t__ tm_sec; scalar_t__ tm_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  date_yesterday (struct tm*,struct tm*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void date_time(struct tm *tm, struct tm *now, int hour)
{
	if (tm->tm_hour < hour)
		date_yesterday(tm, now, NULL);
	tm->tm_hour = hour;
	tm->tm_min = 0;
	tm->tm_sec = 0;
}