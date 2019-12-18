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
 int /*<<< orphan*/  PA_POFF ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_is_r7780mp () ; 
 scalar_t__ mach_is_r7785rp () ; 

__attribute__((used)) static void r7780rp_power_off(void)
{
	if (mach_is_r7780mp() || mach_is_r7785rp())
		__raw_writew(0x0001, PA_POFF);
}