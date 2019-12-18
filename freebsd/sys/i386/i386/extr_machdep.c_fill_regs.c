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
struct trapframe {int dummy; } ;
struct thread {struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct reg {int /*<<< orphan*/  r_gs; } ;
struct pcb {int /*<<< orphan*/  pcb_gs; } ;

/* Variables and functions */
 int fill_frame_regs (struct trapframe*,struct reg*) ; 

int
fill_regs(struct thread *td, struct reg *regs)
{
	struct pcb *pcb;
	struct trapframe *tp;

	tp = td->td_frame;
	pcb = td->td_pcb;
	regs->r_gs = pcb->pcb_gs;
	return (fill_frame_regs(tp, regs));
}