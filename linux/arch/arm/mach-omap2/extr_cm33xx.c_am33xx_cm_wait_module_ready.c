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
 int EBUSY ; 
 int MAX_MODULE_READY_TIME ; 
 int /*<<< orphan*/  _is_module_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_test_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int am33xx_cm_wait_module_ready(u8 part, s16 inst, u16 clkctrl_offs,
				       u8 bit_shift)
{
	int i = 0;

	omap_test_timeout(_is_module_ready(inst, clkctrl_offs),
			  MAX_MODULE_READY_TIME, i);

	return (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
}