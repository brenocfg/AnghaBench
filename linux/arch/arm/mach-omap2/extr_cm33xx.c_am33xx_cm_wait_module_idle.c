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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ CLKCTRL_IDLEST_DISABLED ; 
 int EBUSY ; 
 int MAX_MODULE_READY_TIME ; 
 scalar_t__ _clkctrl_idlest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_test_timeout (int,int,int) ; 

__attribute__((used)) static int am33xx_cm_wait_module_idle(u8 part, s16 inst, u16 clkctrl_offs,
				      u8 bit_shift)
{
	int i = 0;

	omap_test_timeout((_clkctrl_idlest(inst, clkctrl_offs) ==
				CLKCTRL_IDLEST_DISABLED),
				MAX_MODULE_READY_TIME, i);

	return (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
}