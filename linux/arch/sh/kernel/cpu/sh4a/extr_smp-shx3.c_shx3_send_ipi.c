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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __raw_writel (int,unsigned long) ; 

__attribute__((used)) static void shx3_send_ipi(unsigned int cpu, unsigned int message)
{
	unsigned long addr = 0xfe410070 + (cpu * 4);

	BUG_ON(cpu >= 4);

	__raw_writel(1 << (message << 2), addr); /* C0INTICI..CnINTICI */
}