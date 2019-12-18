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
typedef  int u_int ;
struct pcb {int const pcb_flags; int /*<<< orphan*/  pcb_gsbase; int /*<<< orphan*/  pcb_fsbase; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_KGSBASE ; 
 int const PCB_FULL_IRET ; 
 scalar_t__ _ufssel ; 
 scalar_t__ _ugssel ; 
 struct pcb* curpcb ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdfsbase () ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 
 scalar_t__ rfs () ; 
 scalar_t__ rgs () ; 
 int /*<<< orphan*/  set_pcb_flags_raw (struct pcb*,int const) ; 

__attribute__((used)) static void
set_pcb_flags_fsgsbase(struct pcb *pcb, const u_int flags)
{
	register_t r;

	if (curpcb == pcb &&
	    (flags & PCB_FULL_IRET) != 0 &&
	    (pcb->pcb_flags & PCB_FULL_IRET) == 0) {
		r = intr_disable();
		if ((pcb->pcb_flags & PCB_FULL_IRET) == 0) {
			if (rfs() == _ufssel)
				pcb->pcb_fsbase = rdfsbase();
			if (rgs() == _ugssel)
				pcb->pcb_gsbase = rdmsr(MSR_KGSBASE);
		}
		set_pcb_flags_raw(pcb, flags);
		intr_restore(r);
	} else {
		set_pcb_flags_raw(pcb, flags);
	}
}