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
 int /*<<< orphan*/  CPLD_RESET ; 
 int /*<<< orphan*/  nlm_cpld_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_board_cpld_reset(uint64_t base)
{

	nlm_cpld_write(base, CPLD_RESET, 1 << 15);
	for(;;)
		__asm __volatile("wait");
}