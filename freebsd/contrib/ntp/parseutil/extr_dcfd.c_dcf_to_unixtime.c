#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_3__ {scalar_t__ year; int month; int day; scalar_t__ hour; scalar_t__ minute; int utcoffset; scalar_t__ second; } ;
typedef  TYPE_1__ clocktime_t ;

/* Variables and functions */
 int CVT_BADDATE ; 
 int CVT_BADTIME ; 
 int CVT_FAIL ; 
 int /*<<< orphan*/  SETRTC (int) ; 
 int TIMES24 (int) ; 
 int TIMES60 (int) ; 
 scalar_t__ YEAR_BREAK ; 
 scalar_t__ YEAR_PIVOT ; 
 int days_per_year (int) ; 
 int julian0 (int) ; 

__attribute__((used)) static time_t
dcf_to_unixtime(
		clocktime_t   *clock_time,
		unsigned *cvtrtc
		)
{
#define SETRTC(_X_)	{ if (cvtrtc) *cvtrtc = (_X_); }
	static int days_of_month[] =
	{
		0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	register int i;
	time_t t;

	/*
	 * map 2 digit years to 19xx (DCF77 is a 20th century item)
	 */
	if ( clock_time->year < YEAR_PIVOT ) 	/* in case of	   Y2KFixes [ */
		clock_time->year += 100;	/* *year%100, make tm_year */
						/* *(do we need this?) */
	if ( clock_time->year < YEAR_BREAK )	/* (failsafe if) */
	    clock_time->year += 1900;				/* Y2KFixes ] */

	/*
	 * must have been a really bad year code - drop it
	 */
	if (clock_time->year < (YEAR_PIVOT + 1900) )		/* Y2KFixes */
	{
		SETRTC(CVT_FAIL|CVT_BADDATE);
		return -1;
	}
	/*
	 * sorry, slow section here - but it's not time critical anyway
	 */

	/*
	 * calculate days since 1970 (watching leap years)
	 */
	t = julian0( clock_time->year ) - julian0( 1970 );

  				/* month */
	if (clock_time->month <= 0 || clock_time->month > 12)
	{
		SETRTC(CVT_FAIL|CVT_BADDATE);
		return -1;		/* bad month */
	}
				/* adjust current leap year */
#if 0
	if (clock_time->month < 3 && days_per_year(clock_time->year) == 366)
	    t--;
#endif

	/*
	 * collect days from months excluding the current one
	 */
	for (i = 1; i < clock_time->month; i++)
	{
		t += days_of_month[i];
	}
				/* day */
	if (clock_time->day < 1 || ((clock_time->month == 2 && days_per_year(clock_time->year) == 366) ?
			       clock_time->day > 29 : clock_time->day > days_of_month[clock_time->month]))
	{
		SETRTC(CVT_FAIL|CVT_BADDATE);
		return -1;		/* bad day */
	}

	/*
	 * collect days from date excluding the current one
	 */
	t += clock_time->day - 1;

				/* hour */
	if (clock_time->hour < 0 || clock_time->hour >= 24)
	{
		SETRTC(CVT_FAIL|CVT_BADTIME);
		return -1;		/* bad hour */
	}

	/*
	 * calculate hours from 1. 1. 1970
	 */
	t = TIMES24(t) + clock_time->hour;

  				/* min */
	if (clock_time->minute < 0 || clock_time->minute > 59)
	{
		SETRTC(CVT_FAIL|CVT_BADTIME);
		return -1;		/* bad min */
	}

	/*
	 * calculate minutes from 1. 1. 1970
	 */
	t = TIMES60(t) + clock_time->minute;
				/* sec */

	/*
	 * calculate UTC in minutes
	 */
	t += clock_time->utcoffset;

	if (clock_time->second < 0 || clock_time->second > 60)	/* allow for LEAPs */
	{
		SETRTC(CVT_FAIL|CVT_BADTIME);
		return -1;		/* bad sec */
	}

	/*
	 * calculate UTC in seconds - phew !
	 */
	t  = TIMES60(t) + clock_time->second;
				/* done */
	return t;
}