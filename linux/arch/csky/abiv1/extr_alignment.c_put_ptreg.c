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
typedef  int uint32_t ;
struct pt_regs {int lr; int /*<<< orphan*/  a0; } ;

/* Variables and functions */

__attribute__((used)) static inline void put_ptreg(struct pt_regs *regs, uint32_t rx, uint32_t val)
{
	if (rx == 15)
		regs->lr = val;
	else
		*((uint32_t *)&(regs->a0) - 2 + rx) = val;
}