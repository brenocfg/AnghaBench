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
 int CPU_CALL_A_IRQ ; 
 int CPU_RESCHED_A_IRQ ; 
 int /*<<< orphan*/  LOCAL_HUB_CLR_INTR (int) ; 
 int LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCAL_HUB_S (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  PI_CPU_NUM ; 
 int /*<<< orphan*/  PI_INT_MASK0_A ; 
 int /*<<< orphan*/  PI_INT_MASK0_B ; 
 int /*<<< orphan*/  PI_INT_MASK1_A ; 
 int /*<<< orphan*/  PI_INT_MASK1_B ; 
 int /*<<< orphan*/  irq_enable_mask ; 
 unsigned long* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int smp_processor_id () ; 

void install_ipi(void)
{
	int cpu = smp_processor_id();
	unsigned long *mask = per_cpu(irq_enable_mask, cpu);
	int slice = LOCAL_HUB_L(PI_CPU_NUM);
	int resched, call;

	resched = CPU_RESCHED_A_IRQ + slice;
	set_bit(resched, mask);
	LOCAL_HUB_CLR_INTR(resched);

	call = CPU_CALL_A_IRQ + slice;
	set_bit(call, mask);
	LOCAL_HUB_CLR_INTR(call);

	if (slice == 0) {
		LOCAL_HUB_S(PI_INT_MASK0_A, mask[0]);
		LOCAL_HUB_S(PI_INT_MASK1_A, mask[1]);
	} else {
		LOCAL_HUB_S(PI_INT_MASK0_B, mask[0]);
		LOCAL_HUB_S(PI_INT_MASK1_B, mask[1]);
	}
}