#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sibling_subcore_state; int /*<<< orphan*/  paca_index; } ;
struct TYPE_3__ {scalar_t__* in_guest; } ;

/* Variables and functions */
 int cpu_thread_in_core (int /*<<< orphan*/ ) ; 
 int kvmppc_cur_subcore_size () ; 
 TYPE_2__* local_paca ; 

void kvmppc_subcore_exit_guest(void)
{
	int thread_id, subcore_id;

	thread_id = cpu_thread_in_core(local_paca->paca_index);
	subcore_id = thread_id / kvmppc_cur_subcore_size();

	local_paca->sibling_subcore_state->in_guest[subcore_id] = 0;
}