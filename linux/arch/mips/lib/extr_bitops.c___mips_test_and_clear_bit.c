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
 unsigned long SZLONG_LOG ; 
 unsigned long SZLONG_MASK ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 

int __mips_test_and_clear_bit(unsigned long nr, volatile unsigned long *addr)
{
	unsigned long *a = (unsigned long *)addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;
	int res;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a) != 0;
	*a &= ~mask;
	raw_local_irq_restore(flags);
	return res;
}