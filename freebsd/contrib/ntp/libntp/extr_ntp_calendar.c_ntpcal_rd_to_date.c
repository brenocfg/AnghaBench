#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint16_t ;
typedef  int u_int ;
struct calendar {int weekday; void* monthday; void* month; void* yearday; void* year; } ;
struct TYPE_4__ {int hi; scalar_t__ lo; } ;
typedef  TYPE_1__ ntpcal_split ;
typedef  int int32_t ;

/* Variables and functions */
 int DAYSPERWEEK ; 
 TYPE_1__ ntpcal_split_eradays (int,int*) ; 
 TYPE_1__ ntpcal_split_yeardays (scalar_t__,int) ; 

int
ntpcal_rd_to_date(
	struct calendar *jd,
	int32_t		 rd
	)
{
	ntpcal_split split;
	int	     leapy;
	u_int	     ymask;

	/* Get day-of-week first. Since rd is signed, the remainder can
	 * be in the range [-6..+6], but the assignment to an unsigned
	 * variable maps the negative values to positive values >=7.
	 * This makes the sign correction look strange, but adding 7
	 * causes the needed wrap-around into the desired value range of
	 * zero to six, both inclusive.
	 */
	jd->weekday = rd % DAYSPERWEEK;
	if (jd->weekday >= DAYSPERWEEK)	/* weekday is unsigned! */
		jd->weekday += DAYSPERWEEK;

	split = ntpcal_split_eradays(rd - 1, &leapy);
	/* Get year and day-of-year, with overflow check. If any of the
	 * upper 16 bits is set after shifting to unity-based years, we
	 * will have an overflow when converting to an unsigned 16bit
	 * year. Shifting to the right is OK here, since it does not
	 * matter if the shift is logic or arithmetic.
	 */
	split.hi += 1;
	ymask = 0u - ((split.hi >> 16) == 0);
	jd->year = (uint16_t)(split.hi & ymask);
	jd->yearday = (uint16_t)split.lo + 1;

	/* convert to month and mday */
	split = ntpcal_split_yeardays(split.lo, leapy);
	jd->month    = (uint8_t)split.hi + 1;
	jd->monthday = (uint8_t)split.lo + 1;

	return ymask ? leapy : -1;
}