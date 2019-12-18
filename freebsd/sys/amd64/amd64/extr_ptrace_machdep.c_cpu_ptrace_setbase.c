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
struct thread {TYPE_1__* td_frame; struct pcb* td_pcb; } ;
struct pcb {void* pcb_gsbase; void* pcb_fsbase; } ;
typedef  void* register_t ;
struct TYPE_2__ {int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int PT_SETFSBASE ; 
 int /*<<< orphan*/  _ufssel ; 
 int /*<<< orphan*/  _ugssel ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpu_ptrace_setbase(struct thread *td, int req, register_t r)
{
	struct pcb *pcb;

	pcb = td->td_pcb;
	set_pcb_flags(pcb, PCB_FULL_IRET);
	if (req == PT_SETFSBASE) {
		pcb->pcb_fsbase = r;
		td->td_frame->tf_fs = _ufssel;
	} else {
		pcb->pcb_gsbase = r;
		td->td_frame->tf_gs = _ugssel;
	}
}