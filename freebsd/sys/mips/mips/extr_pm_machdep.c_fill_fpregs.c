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
struct thread {TYPE_1__* td_frame; } ;
struct fpreg {int /*<<< orphan*/ * r_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  fpu_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 size_t FIR_NUM ; 
 int /*<<< orphan*/  MipsSaveCurFPState (struct thread*) ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 TYPE_2__ cpuinfo ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  memcpy (struct fpreg*,int /*<<< orphan*/ *,int) ; 

int
fill_fpregs(struct thread *td, struct fpreg *fpregs)
{
	if (td == PCPU_GET(fpcurthread))
		MipsSaveCurFPState(td);
	memcpy(fpregs, &td->td_frame->f0, sizeof(struct fpreg));
	fpregs->r_regs[FIR_NUM] = cpuinfo.fpu_id;
	return 0;
}