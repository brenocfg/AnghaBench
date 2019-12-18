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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ pcic_regs; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ PCI_SYS_COUNTER ; 
 int PCI_SYS_COUNTER_OVERFLOW ; 
 int TICK_TIMER_LIMIT ; 
 int USECS_PER_JIFFY ; 
 TYPE_1__ pcic0 ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int pcic_cycles_offset(void)
{
	u32 value, count;

	value = readl(pcic0.pcic_regs + PCI_SYS_COUNTER);
	count = value & ~PCI_SYS_COUNTER_OVERFLOW;

	if (value & PCI_SYS_COUNTER_OVERFLOW)
		count += TICK_TIMER_LIMIT;
	/*
	 * We divide all by HZ
	 * to have microsecond resolution and to avoid overflow
	 */
	count = ((count / HZ) * USECS_PER_JIFFY) / (TICK_TIMER_LIMIT / HZ);

	/* Coordinate with the sparc_config.clock_rate setting */
	return count * 2;
}