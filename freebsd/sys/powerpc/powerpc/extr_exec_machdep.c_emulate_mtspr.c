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
struct trapframe {int srr0; int /*<<< orphan*/ * fixreg; } ;
struct thread {TYPE_1__* td_pcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_dscr; int /*<<< orphan*/  pcb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_CDSCR ; 
 int PPC_FEATURE2_DSCR ; 
 int SIGILL ; 
 int SPR_DSCR ; 
 int SPR_DSCRP ; 
 int cpu_features2 ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtspr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emulate_mtspr(int spr, int reg, struct trapframe *frame){
	struct thread *td;

	td = curthread;

	if (spr == SPR_DSCR || spr == SPR_DSCRP) {
		if (!(cpu_features2 & PPC_FEATURE2_DSCR))
			return (SIGILL);
		td->td_pcb->pcb_flags |= PCB_CDSCR;
		td->td_pcb->pcb_dscr = frame->fixreg[reg];
		mtspr(SPR_DSCRP, frame->fixreg[reg]);
		frame->srr0 += 4;
		return (0);
	} else
		return (SIGILL);
}