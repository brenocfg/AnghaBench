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
struct thread {struct pcb* td_pcb; TYPE_1__* td_frame; } ;
struct pcb {int pcb_dr0; int pcb_dr1; int pcb_dr2; int pcb_dr3; int pcb_dr6; int pcb_dr7; } ;
struct dbreg {int* dr; } ;
struct TYPE_2__ {scalar_t__ tf_cs; } ;

/* Variables and functions */
 int DBREG_DR7_ACCESS (int,int) ; 
 scalar_t__ DBREG_DR7_ENABLED (int,int) ; 
 scalar_t__ DBREG_DR7_LEN (int,int) ; 
 scalar_t__ DBREG_DR7_LEN_8 ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCB_DBREGS ; 
 int VM_MAXUSER_ADDRESS ; 
 scalar_t__ _ucode32sel ; 
 int /*<<< orphan*/  load_dr0 (int) ; 
 int /*<<< orphan*/  load_dr1 (int) ; 
 int /*<<< orphan*/  load_dr2 (int) ; 
 int /*<<< orphan*/  load_dr3 (int) ; 
 int /*<<< orphan*/  load_dr6 (int) ; 
 int /*<<< orphan*/  load_dr7 (int) ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int /*<<< orphan*/ ) ; 

int
set_dbregs(struct thread *td, struct dbreg *dbregs)
{
	struct pcb *pcb;
	int i;

	if (td == NULL) {
		load_dr0(dbregs->dr[0]);
		load_dr1(dbregs->dr[1]);
		load_dr2(dbregs->dr[2]);
		load_dr3(dbregs->dr[3]);
		load_dr6(dbregs->dr[6]);
		load_dr7(dbregs->dr[7]);
	} else {
		/*
		 * Don't let an illegal value for dr7 get set.  Specifically,
		 * check for undefined settings.  Setting these bit patterns
		 * result in undefined behaviour and can lead to an unexpected
		 * TRCTRAP or a general protection fault right here.
		 * Upper bits of dr6 and dr7 must not be set
		 */
		for (i = 0; i < 4; i++) {
			if (DBREG_DR7_ACCESS(dbregs->dr[7], i) == 0x02)
				return (EINVAL);
			if (td->td_frame->tf_cs == _ucode32sel &&
			    DBREG_DR7_LEN(dbregs->dr[7], i) == DBREG_DR7_LEN_8)
				return (EINVAL);
		}
		if ((dbregs->dr[6] & 0xffffffff00000000ul) != 0 ||
		    (dbregs->dr[7] & 0xffffffff00000000ul) != 0)
			return (EINVAL);

		pcb = td->td_pcb;

		/*
		 * Don't let a process set a breakpoint that is not within the
		 * process's address space.  If a process could do this, it
		 * could halt the system by setting a breakpoint in the kernel
		 * (if ddb was enabled).  Thus, we need to check to make sure
		 * that no breakpoints are being enabled for addresses outside
		 * process's address space.
		 *
		 * XXX - what about when the watched area of the user's
		 * address space is written into from within the kernel
		 * ... wouldn't that still cause a breakpoint to be generated
		 * from within kernel mode?
		 */

		if (DBREG_DR7_ENABLED(dbregs->dr[7], 0)) {
			/* dr0 is enabled */
			if (dbregs->dr[0] >= VM_MAXUSER_ADDRESS)
				return (EINVAL);
		}
		if (DBREG_DR7_ENABLED(dbregs->dr[7], 1)) {
			/* dr1 is enabled */
			if (dbregs->dr[1] >= VM_MAXUSER_ADDRESS)
				return (EINVAL);
		}
		if (DBREG_DR7_ENABLED(dbregs->dr[7], 2)) {
			/* dr2 is enabled */
			if (dbregs->dr[2] >= VM_MAXUSER_ADDRESS)
				return (EINVAL);
		}
		if (DBREG_DR7_ENABLED(dbregs->dr[7], 3)) {
			/* dr3 is enabled */
			if (dbregs->dr[3] >= VM_MAXUSER_ADDRESS)
				return (EINVAL);
		}

		pcb->pcb_dr0 = dbregs->dr[0];
		pcb->pcb_dr1 = dbregs->dr[1];
		pcb->pcb_dr2 = dbregs->dr[2];
		pcb->pcb_dr3 = dbregs->dr[3];
		pcb->pcb_dr6 = dbregs->dr[6];
		pcb->pcb_dr7 = dbregs->dr[7];

		set_pcb_flags(pcb, PCB_DBREGS);
	}

	return (0);
}