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
typedef  scalar_t__ u64 ;

/* Variables and functions */

__attribute__((used)) static void extend_address_range(u64 *start, u64 *stop, u64 estart, int len)
{
	u64 estop;

	if (len > 0)
		len--;
	else
		len = 0;

	estop = estart + len;

	/* 0-0 range represents "not set" */
	if ((*start == 0) && (*stop == 0)) {
		*start = estart;
		*stop = estop;
	} else if (*start <= *stop) {
		/* increase the existing range */
		if (estart < *start)
			*start = estart;
		if (estop > *stop)
			*stop = estop;
	} else {
		/* "overflowing" interval, whereby *stop > *start */
		if (estart <= *stop) {
			if (estop > *stop)
				*stop = estop;
		} else if (estop > *start) {
			if (estart < *start)
				*start = estart;
		}
		/* minimize the range */
		else if ((estop - *stop) < (*start - estart))
			*stop = estop;
		else
			*start = estart;
	}
}