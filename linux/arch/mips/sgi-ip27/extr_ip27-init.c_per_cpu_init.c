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
struct hub_data {int /*<<< orphan*/  slice_map; } ;
typedef  int /*<<< orphan*/  cnodeid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP27_HUB_PEND0_IRQ ; 
 int /*<<< orphan*/  IP27_HUB_PEND1_IRQ ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI_CPU_NUM ; 
 int /*<<< orphan*/  ST0_IM ; 
 int /*<<< orphan*/  clear_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_time_init () ; 
 int /*<<< orphan*/  cputoslice (int) ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_compact_nodeid () ; 
 struct hub_data* hub_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_cpu_nmi_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_ipi () ; 
 int /*<<< orphan*/  per_hub_init (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

void per_cpu_init(void)
{
	int cpu = smp_processor_id();
	int slice = LOCAL_HUB_L(PI_CPU_NUM);
	cnodeid_t cnode = get_compact_nodeid();
	struct hub_data *hub = hub_data(cnode);

	if (test_and_set_bit(slice, &hub->slice_map))
		return;

	clear_c0_status(ST0_IM);

	per_hub_init(cnode);

	cpu_time_init();
	install_ipi();

	/* Install our NMI handler if symmon hasn't installed one. */
	install_cpu_nmi_handler(cputoslice(cpu));

	enable_percpu_irq(IP27_HUB_PEND0_IRQ, IRQ_TYPE_NONE);
	enable_percpu_irq(IP27_HUB_PEND1_IRQ, IRQ_TYPE_NONE);
}