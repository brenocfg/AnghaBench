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
typedef  int /*<<< orphan*/  u_long ;
struct trapframe {int /*<<< orphan*/  tf_sepc; int /*<<< orphan*/  tf_ra; int /*<<< orphan*/  tf_sp; int /*<<< orphan*/ * tf_a; } ;
struct thread {struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct pcb {int /*<<< orphan*/  pcb_fpflags; } ;
struct image_params {int /*<<< orphan*/  entry_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_FP_STARTED ; 
 int /*<<< orphan*/  STACKALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct trapframe*,int /*<<< orphan*/ ,int) ; 

void
exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	struct trapframe *tf;
	struct pcb *pcb;

	tf = td->td_frame;
	pcb = td->td_pcb;

	memset(tf, 0, sizeof(struct trapframe));

	tf->tf_a[0] = stack;
	tf->tf_sp = STACKALIGN(stack);
	tf->tf_ra = imgp->entry_addr;
	tf->tf_sepc = imgp->entry_addr;

	pcb->pcb_fpflags &= ~PCB_FP_STARTED;
}