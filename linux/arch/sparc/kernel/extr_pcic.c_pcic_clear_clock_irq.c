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
struct TYPE_2__ {scalar_t__ pcic_regs; } ;

/* Variables and functions */
 scalar_t__ PCI_SYS_LIMIT ; 
 TYPE_1__ pcic0 ; 
 int /*<<< orphan*/  pcic_timer_dummy ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void pcic_clear_clock_irq(void)
{
	pcic_timer_dummy = readl(pcic0.pcic_regs+PCI_SYS_LIMIT);
}