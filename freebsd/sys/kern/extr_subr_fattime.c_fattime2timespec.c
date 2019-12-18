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
struct timespec {unsigned int tv_sec; unsigned int tv_nsec; } ;

/* Variables and functions */
 unsigned int DAY ; 
 int FEB ; 
 unsigned int LYC ; 
 scalar_t__ T1980 ; 
 scalar_t__* daytab ; 
 scalar_t__ utc_offset () ; 

void
fattime2timespec(unsigned dd, unsigned dt, unsigned dh, int utc,
    struct timespec *tsp)
{
	unsigned day;

	/* Unpack time fields */
	tsp->tv_sec = (dt & 0x1f) << 1;
	tsp->tv_sec += ((dt & 0x7e0) >> 5) * 60;
	tsp->tv_sec += ((dt & 0xf800) >> 11) * 3600;
	tsp->tv_sec += dh / 100;
	tsp->tv_nsec = (dh % 100) * 10000000;

	/* Day of month */
	day = (dd & 0x1f) - 1;

	/* Full leap-year cycles */
	day += LYC * ((dd >> 11) & 0x1f);

	/* Month offset from leap-year cycle */
	day += daytab[(dd >> 5) & 0x3f];

	/*
	 * 2100 is not a leap year.
	 * XXX: a 32 bit time_t can not get us here.
	 */
	if (day >= ((2100 - 1980) / 4 * LYC + FEB))
		day--;

	/* Align with time_t epoch */
	day += T1980;

	tsp->tv_sec += DAY * day;
	if (!utc)
		tsp->tv_sec += utc_offset();
}