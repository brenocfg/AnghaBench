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
typedef  scalar_t__ time_t ;
struct TYPE_3__ {int Year; int Month; int Day; int Hour; int Minute; int Second; int TimeZone; } ;
typedef  TYPE_1__ EFI_TIME ;

/* Variables and functions */
 int** CumulativeDays ; 
 int EFI_UNSPECIFIED_TIMEZONE ; 
 int SECSPERDAY ; 
 int SECSPERHOUR ; 
 size_t isleap (int) ; 

time_t
from_efi_time(EFI_TIME *ETime)
{
	time_t  UTime;
	int	Year;

	/*
	 *  Do a santity check
	 */
	if (ETime->Year  <  1998 || ETime->Year   > 2099 ||
	    ETime->Month ==    0 || ETime->Month  >   12 ||
	    ETime->Day   ==    0 || ETime->Month  >   31 ||
	    ETime->Hour   >   23 || ETime->Minute >   59 ||
	    ETime->Second >   59 || ETime->TimeZone  < -1440 ||
	    (ETime->TimeZone >  1440 && ETime->TimeZone != 2047)) {
		return (0);
	}

	/*
	 * Years
	 */
	UTime = 0;
	for (Year = 1970; Year != ETime->Year; ++Year) {
		UTime += (CumulativeDays[isleap(Year)][13] * SECSPERDAY);
	}

	/*
	 * UTime should now be set to 00:00:00 on Jan 1 of the file's year.
	 *
	 * Months  
	 */
	UTime += (CumulativeDays[isleap(ETime->Year)][ETime->Month] *
	    SECSPERDAY);

	/*
	 * UTime should now be set to 00:00:00 on the first of the file's
	 * month and year.
	 *
	 * Days -- Don't count the file's day
	 */
	UTime += (((ETime->Day > 0) ? ETime->Day-1:0) * SECSPERDAY);

	/*
	 * Hours
	 */
	UTime += (ETime->Hour * SECSPERHOUR);

	/*
	 * Minutes
	 */
	UTime += (ETime->Minute * 60);

	/*
	 * Seconds
	 */
	UTime += ETime->Second;

	/*
	 * EFI time is repored in local time.  Adjust for any time zone
	 * offset to get true UT
	 */
	if (ETime->TimeZone != EFI_UNSPECIFIED_TIMEZONE) {
		/*
		 * TimeZone is kept in minues...
		 */
		UTime += (ETime->TimeZone * 60);
	}

	return (UTime);
}