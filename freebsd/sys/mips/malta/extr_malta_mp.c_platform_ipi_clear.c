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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_SW1 ; 
 int /*<<< orphan*/  mips_rd_cause () ; 
 int /*<<< orphan*/  mips_wr_cause (int /*<<< orphan*/ ) ; 

void
platform_ipi_clear(void)
{
	uint32_t reg;

	reg = mips_rd_cause();
	reg &= ~(C_SW1);
	mips_wr_cause(reg);
}