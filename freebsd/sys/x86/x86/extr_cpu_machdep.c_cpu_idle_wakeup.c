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
struct monitorbuf {int idle_state; } ;
struct TYPE_2__ {struct monitorbuf pc_monitorbuf; } ;

/* Variables and functions */
#define  STATE_MWAIT 130 
#define  STATE_RUNNING 129 
#define  STATE_SLEEPING 128 
 int atomic_load_int (int*) ; 
 int /*<<< orphan*/  atomic_store_int (int*,int) ; 
 int /*<<< orphan*/  cpu_idle_apl31_workaround ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* pcpu_find (int) ; 

int
cpu_idle_wakeup(int cpu)
{
	struct monitorbuf *mb;
	int *state;

	mb = &pcpu_find(cpu)->pc_monitorbuf;
	state = &mb->idle_state;
	switch (atomic_load_int(state)) {
	case STATE_SLEEPING:
		return (0);
	case STATE_MWAIT:
		atomic_store_int(state, STATE_RUNNING);
		return (cpu_idle_apl31_workaround ? 0 : 1);
	case STATE_RUNNING:
		return (1);
	default:
		panic("bad monitor state");
		return (1);
	}
}