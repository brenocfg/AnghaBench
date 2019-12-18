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
 unsigned int __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  __raw_writew (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilsel_level_map ; 
 unsigned long mk_ilsel_addr (unsigned int) ; 
 int mk_ilsel_shift (unsigned int) ; 
 int /*<<< orphan*/  pr_notice (char*,unsigned int) ; 

void ilsel_disable(unsigned int irq)
{
	unsigned long addr;
	unsigned int tmp;

	pr_notice("disabling ILSEL set %d\n", irq);

	addr = mk_ilsel_addr(irq);

	tmp = __raw_readw(addr);
	tmp &= ~(0xf << mk_ilsel_shift(irq));
	__raw_writew(tmp, addr);

	clear_bit(irq, &ilsel_level_map);
}