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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CHIP_RESET ; 
 int /*<<< orphan*/  nlm_get_sys_regbase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_sys_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
platform_reset(void)
{
	uint64_t sysbase = nlm_get_sys_regbase(0);

	nlm_write_sys_reg(sysbase, SYS_CHIP_RESET, 1);
	for( ; ; )
		__asm __volatile("wait");
}