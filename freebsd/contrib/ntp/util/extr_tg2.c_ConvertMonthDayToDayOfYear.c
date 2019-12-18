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
 scalar_t__ Debug ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

int
ConvertMonthDayToDayOfYear (int YearValue, int MonthValue, int DayOfMonthValue)
	{
	int	ReturnValue;
	int	LeapYear;
	int	MonthCounter;

	/* Array of days in a month.  Note that here January is zero. */
	/* NB: have to add 1 to days in February in a leap year! */
	int DaysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


	LeapYear = FALSE;
	if  ((YearValue % 4) == 0)
		{
		if  ((YearValue % 100) == 0)
			{
			if  ((YearValue % 400) == 0)
				{
				LeapYear = TRUE;
				}
			}
		else
			{
			LeapYear = TRUE;
			}
		}

	if  (Debug)
		printf ("\nConvertMonthDayToDayOfYear(): Year %d %s a leap year.\n", YearValue+2000, LeapYear ? "is" : "is not");

	/* Day of month given us starts in this algorithm. */
	ReturnValue = DayOfMonthValue;

	/* Add in days in month for each month past January. */
	for (MonthCounter=1; MonthCounter<MonthValue; MonthCounter++)
		{
		ReturnValue += DaysInMonth [ MonthCounter - 1 ];
		}

	/* Add a day for leap years where we are past February. */
	if  ((LeapYear) && (MonthValue > 2))
		{
		ReturnValue++;
		}

	if  (Debug)
		printf ("\nConvertMonthDayToDayOfYear(): %4.4d-%2.2d-%2.2d represents day %3d of year.\n",
				YearValue+2000, MonthValue, DayOfMonthValue, ReturnValue);

	return (ReturnValue);
	}