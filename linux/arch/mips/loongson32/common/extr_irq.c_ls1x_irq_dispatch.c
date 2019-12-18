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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  LS1X_INTC_INTIEN (int) ; 
 int /*<<< orphan*/  LS1X_INTC_INTISR (int) ; 
 int LS1X_IRQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ffs (int) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 

__attribute__((used)) static void ls1x_irq_dispatch(int n)
{
	u32 int_status, irq;

	/* Get pending sources, masked by current enables */
	int_status = __raw_readl(LS1X_INTC_INTISR(n)) &
			__raw_readl(LS1X_INTC_INTIEN(n));

	if (int_status) {
		irq = LS1X_IRQ(n, __ffs(int_status));
		do_IRQ(irq);
	}
}