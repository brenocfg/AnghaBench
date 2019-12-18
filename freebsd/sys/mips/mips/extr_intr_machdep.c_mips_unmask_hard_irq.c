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
 int mips_rd_status () ; 
 int /*<<< orphan*/  mips_wr_status (int) ; 

__attribute__((used)) static void
mips_unmask_hard_irq(void *source)
{
	uintptr_t irq = (uintptr_t)source;

	mips_wr_status(mips_rd_status() | (((1 << irq) << 8) << 2));
}