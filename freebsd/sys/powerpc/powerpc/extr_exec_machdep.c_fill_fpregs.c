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
struct thread {struct pcb* td_pcb; } ;
struct TYPE_4__ {TYPE_1__* fpr; int /*<<< orphan*/  fpscr; } ;
struct pcb {int pcb_flags; TYPE_2__ pcb_fpu; } ;
struct fpreg {int /*<<< orphan*/ * fpreg; int /*<<< orphan*/  fpscr; } ;
struct TYPE_3__ {int /*<<< orphan*/  fpr; } ;

/* Variables and functions */
 int PCB_FPREGS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct fpreg*,int /*<<< orphan*/ ,int) ; 

int
fill_fpregs(struct thread *td, struct fpreg *fpregs)
{
	struct pcb *pcb;
	int i;

	pcb = td->td_pcb;

	if ((pcb->pcb_flags & PCB_FPREGS) == 0)
		memset(fpregs, 0, sizeof(struct fpreg));
	else {
		memcpy(&fpregs->fpscr, &pcb->pcb_fpu.fpscr, sizeof(double));
		for (i = 0; i < 32; i++)
			memcpy(&fpregs->fpreg[i], &pcb->pcb_fpu.fpr[i].fpr,
			    sizeof(double));
	}

	return (0);
}