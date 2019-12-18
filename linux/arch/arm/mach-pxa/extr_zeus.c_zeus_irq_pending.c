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
 int /*<<< orphan*/  ZEUS_CPLD_ISA_IRQ ; 
 unsigned long __raw_readw (int /*<<< orphan*/ ) ; 
 unsigned long zeus_irq_enabled_mask ; 

__attribute__((used)) static inline unsigned long zeus_irq_pending(void)
{
	return __raw_readw(ZEUS_CPLD_ISA_IRQ) & zeus_irq_enabled_mask;
}