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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */

__attribute__((used)) static inline int nodate(struct tm *tm)
{
	return (tm->tm_year &
		tm->tm_mon &
		tm->tm_mday &
		tm->tm_hour &
		tm->tm_min &
		tm->tm_sec) < 0;
}