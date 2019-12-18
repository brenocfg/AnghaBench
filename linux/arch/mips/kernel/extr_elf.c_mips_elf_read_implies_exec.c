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
 int EXSTACK_DISABLE_X ; 
 int /*<<< orphan*/  cpu_has_rixi ; 

int mips_elf_read_implies_exec(void *elf_ex, int exstack)
{
	if (exstack != EXSTACK_DISABLE_X) {
		/* The binary doesn't request a non-executable stack */
		return 1;
	}

	if (!cpu_has_rixi) {
		/* The CPU doesn't support non-executable memory */
		return 1;
	}

	return 0;
}