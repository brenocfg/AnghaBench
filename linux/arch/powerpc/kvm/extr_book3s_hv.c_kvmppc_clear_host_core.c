#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* rm_core; } ;
struct TYPE_4__ {scalar_t__ in_host; } ;
struct TYPE_5__ {TYPE_1__ rm_state; } ;

/* Variables and functions */
 scalar_t__ cpu_thread_in_core (unsigned int) ; 
 TYPE_3__* kvmppc_host_rm_ops_hv ; 
 unsigned int threads_shift ; 

__attribute__((used)) static inline int kvmppc_clear_host_core(unsigned int cpu)
{
	int core;

	if (!kvmppc_host_rm_ops_hv || cpu_thread_in_core(cpu))
		return 0;
	/*
	 * Memory barrier can be omitted here as we will do a smp_wmb()
	 * later in kvmppc_start_thread and we need ensure that state is
	 * visible to other CPUs only after we enter guest.
	 */
	core = cpu >> threads_shift;
	kvmppc_host_rm_ops_hv->rm_core[core].rm_state.in_host = 0;
	return 0;
}