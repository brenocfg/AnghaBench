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
struct mid_pwr {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int mid_pwr_is_busy (struct mid_pwr*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mid_pwr_wait(struct mid_pwr *pwr)
{
	unsigned int count = 500000;
	bool busy;

	do {
		busy = mid_pwr_is_busy(pwr);
		if (!busy)
			return 0;
		udelay(1);
	} while (--count);

	return -EBUSY;
}