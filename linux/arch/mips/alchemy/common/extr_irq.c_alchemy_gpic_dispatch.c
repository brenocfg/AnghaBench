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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALCHEMY_GPIC_INT_BASE ; 
 scalar_t__ AU1300_GPIC_ADDR ; 
 scalar_t__ AU1300_GPIC_PRIENC ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 

__attribute__((used)) static void alchemy_gpic_dispatch(struct irq_desc *d)
{
	int i = __raw_readl(AU1300_GPIC_ADDR + AU1300_GPIC_PRIENC);
	generic_handle_irq(ALCHEMY_GPIC_INT_BASE + i);
}