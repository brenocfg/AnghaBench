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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mailbox_0_set_regs ; 

__attribute__((used)) static void bcm1480_send_ipi_single(int cpu, unsigned int action)
{
	__raw_writeq((((u64)action)<< 48), mailbox_0_set_regs[cpu]);
}