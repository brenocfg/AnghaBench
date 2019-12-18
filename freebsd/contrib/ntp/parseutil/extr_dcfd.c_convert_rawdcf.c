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
struct TYPE_3__ {int minute; int hour; int day; int month; int year; int wday; int utcoffset; int /*<<< orphan*/  flags; scalar_t__ second; scalar_t__ usecond; } ;
typedef  TYPE_1__ clocktime_t ;

/* Variables and functions */
 unsigned long CVT_BADFMT ; 
 unsigned long CVT_FAIL ; 
 unsigned long CVT_NONE ; 
 unsigned long CVT_OK ; 
 int /*<<< orphan*/  DCFB_ANNOUNCE ; 
 int /*<<< orphan*/  DCFB_CALLBIT ; 
 int /*<<< orphan*/  DCFB_DST ; 
 int /*<<< orphan*/  DCFB_LEAP ; 
 int /*<<< orphan*/  DCF_A1 ; 
 int /*<<< orphan*/  DCF_A2 ; 
 int /*<<< orphan*/  DCF_D1 ; 
 int /*<<< orphan*/  DCF_D10 ; 
 int /*<<< orphan*/  DCF_DW ; 
 int /*<<< orphan*/  DCF_H1 ; 
 int /*<<< orphan*/  DCF_H10 ; 
 int /*<<< orphan*/  DCF_M1 ; 
 int /*<<< orphan*/  DCF_M10 ; 
 int /*<<< orphan*/  DCF_MO ; 
 int /*<<< orphan*/  DCF_MO0 ; 
 int /*<<< orphan*/  DCF_P_P1 ; 
 int /*<<< orphan*/  DCF_P_P2 ; 
 int /*<<< orphan*/  DCF_P_P3 ; 
 int /*<<< orphan*/  DCF_R ; 
 int /*<<< orphan*/  DCF_S ; 
 int /*<<< orphan*/  DCF_Y1 ; 
 int /*<<< orphan*/  DCF_Y10 ; 
 int /*<<< orphan*/  DCF_Z ; 
#define  DCF_Z_MED 129 
#define  DCF_Z_MET 128 
 int /*<<< orphan*/  PRINTF (char*,char*) ; 
 int TIMES10 (int) ; 
 int ext_bf (unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pcheck (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
convert_rawdcf(
	       unsigned char   *buffer,
	       int              size,
	       clocktime_t     *clock_time
	       )
{
	if (size < 57)
	{
		PRINTF("%-30s", "*** INCOMPLETE");
		return CVT_NONE;
	}

	/*
	 * check Start and Parity bits
	 */
	if ((ext_bf(buffer, DCF_S) == 1) &&
	    pcheck(buffer, DCF_P_P1) &&
	    pcheck(buffer, DCF_P_P2) &&
	    pcheck(buffer, DCF_P_P3))
	{
		/*
		 * buffer OK - extract all fields and build wall clock time from them
		 */

		clock_time->flags  = 0;
		clock_time->usecond= 0;
		clock_time->second = 0;
		clock_time->minute = ext_bf(buffer, DCF_M10);
		clock_time->minute = TIMES10(clock_time->minute) + ext_bf(buffer, DCF_M1);
		clock_time->hour   = ext_bf(buffer, DCF_H10);
		clock_time->hour   = TIMES10(clock_time->hour)   + ext_bf(buffer, DCF_H1);
		clock_time->day    = ext_bf(buffer, DCF_D10);
		clock_time->day    = TIMES10(clock_time->day)    + ext_bf(buffer, DCF_D1);
		clock_time->month  = ext_bf(buffer, DCF_MO0);
		clock_time->month  = TIMES10(clock_time->month)  + ext_bf(buffer, DCF_MO);
		clock_time->year   = ext_bf(buffer, DCF_Y10);
		clock_time->year   = TIMES10(clock_time->year)   + ext_bf(buffer, DCF_Y1);
		clock_time->wday   = ext_bf(buffer, DCF_DW);

		/*
		 * determine offset to UTC by examining the time zone
		 */
		switch (ext_bf(buffer, DCF_Z))
		{
		    case DCF_Z_MET:
			clock_time->utcoffset = -60;
			break;

		    case DCF_Z_MED:
			clock_time->flags     |= DCFB_DST;
			clock_time->utcoffset  = -120;
			break;

		    default:
			PRINTF("%-30s", "*** BAD TIME ZONE");
			return CVT_FAIL|CVT_BADFMT;
		}

		/*
		 * extract various warnings from DCF77
		 */
		if (ext_bf(buffer, DCF_A1))
		    clock_time->flags |= DCFB_ANNOUNCE;

		if (ext_bf(buffer, DCF_A2))
		    clock_time->flags |= DCFB_LEAP;

		if (ext_bf(buffer, DCF_R))
		    clock_time->flags |= DCFB_CALLBIT;

		return CVT_OK;
	}
	else
	{
		/*
		 * bad format - not for us
		 */
		PRINTF("%-30s", "*** BAD FORMAT (invalid/parity)");
		return CVT_FAIL|CVT_BADFMT;
	}
}