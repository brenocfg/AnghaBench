#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct admhcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  admhc_readl (struct admhcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  admhc_writel (struct admhcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void admhc_intr_enable(struct admhcd *ahcd, u32 ints)
{
	u32	t;

	t = admhc_readl(ahcd, &ahcd->regs->int_enable);
	t |= ints;
	admhc_writel(ahcd, t, &ahcd->regs->int_enable);
	/* TODO: flush writes ?*/
}