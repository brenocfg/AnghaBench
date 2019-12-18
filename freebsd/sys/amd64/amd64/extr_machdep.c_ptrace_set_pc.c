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
struct thread {int /*<<< orphan*/  td_pcb; TYPE_1__* td_frame; } ;
struct TYPE_2__ {unsigned long tf_rip; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ptrace_set_pc(struct thread *td, unsigned long addr)
{

	td->td_frame->tf_rip = addr;
	set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
	return (0);
}