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
struct TYPE_2__ {int /*<<< orphan*/  tpmnmimr0; int /*<<< orphan*/  tpmmcmr0; int /*<<< orphan*/  tpmcimr0; int /*<<< orphan*/  tpmimr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,unsigned int) ; 
 int get_hard_smp_processor_id (int) ; 
 TYPE_1__* rcpm_v2_regs ; 

__attribute__((used)) static void rcpm_v2_irq_unmask(int cpu)
{
	int hw_cpu = get_hard_smp_processor_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	clrbits32(&rcpm_v2_regs->tpmimr0, mask);
	clrbits32(&rcpm_v2_regs->tpmcimr0, mask);
	clrbits32(&rcpm_v2_regs->tpmmcmr0, mask);
	clrbits32(&rcpm_v2_regs->tpmnmimr0, mask);
}