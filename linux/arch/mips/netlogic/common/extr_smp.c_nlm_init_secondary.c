#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  package; } ;

/* Variables and functions */
 int NLM_THREADS_PER_CORE ; 
 int /*<<< orphan*/  cpu_set_core (TYPE_1__*,int) ; 
 TYPE_1__ current_cpu_data ; 
 int hard_smp_processor_id () ; 
 int /*<<< orphan*/  nlm_nodeid () ; 
 int /*<<< orphan*/  nlm_percpu_init (int) ; 
 int /*<<< orphan*/  nlm_smp_irq_init (int) ; 

__attribute__((used)) static void nlm_init_secondary(void)
{
	int hwtid;

	hwtid = hard_smp_processor_id();
	cpu_set_core(&current_cpu_data, hwtid / NLM_THREADS_PER_CORE);
	current_cpu_data.package = nlm_nodeid();
	nlm_percpu_init(hwtid);
	nlm_smp_irq_init(hwtid);
}