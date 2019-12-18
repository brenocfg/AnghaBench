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
 int C_IRQ0 ; 
 int C_IRQ1 ; 
 int C_IRQ2 ; 
 int C_IRQ3 ; 
 int C_IRQ5 ; 
 scalar_t__ MIPS_CPU_IRQ_BASE ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int /*<<< orphan*/  pcit_hwint0 () ; 
 int read_c0_cause () ; 
 int read_c0_status () ; 

__attribute__((used)) static void sni_pcit_hwint_cplus(void)
{
	u32 pending = read_c0_cause() & read_c0_status();

	if (pending & C_IRQ0)
		pcit_hwint0();
	else if (pending & C_IRQ1)
		do_IRQ(MIPS_CPU_IRQ_BASE + 3);
	else if (pending & C_IRQ2)
		do_IRQ(MIPS_CPU_IRQ_BASE + 4);
	else if (pending & C_IRQ3)
		do_IRQ(MIPS_CPU_IRQ_BASE + 5);
	else if (pending & C_IRQ5)
		do_IRQ(MIPS_CPU_IRQ_BASE + 7);
}