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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  mpc885_get_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc8xx_set_clocks (int /*<<< orphan*/ ) ; 

int mpc885_fixup_clocks(u32 crystal)
{
	u32 sysclk = mpc885_get_clock(crystal);
	if (!sysclk)
		return 0;

	mpc8xx_set_clocks(sysclk);
	return 1;
}