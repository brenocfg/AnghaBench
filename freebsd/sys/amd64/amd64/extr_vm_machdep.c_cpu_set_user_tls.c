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
typedef  scalar_t__ u_int64_t ;
struct thread {int /*<<< orphan*/  td_proc; struct pcb* td_pcb; } ;
struct pcb {void* pcb_fsbase; void* pcb_gsbase; } ;
typedef  void* register_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int /*<<< orphan*/ ) ; 

int
cpu_set_user_tls(struct thread *td, void *tls_base)
{
	struct pcb *pcb;

	if ((u_int64_t)tls_base >= VM_MAXUSER_ADDRESS)
		return (EINVAL);

	pcb = td->td_pcb;
	set_pcb_flags(pcb, PCB_FULL_IRET);
#ifdef COMPAT_FREEBSD32
	if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
		pcb->pcb_gsbase = (register_t)tls_base;
		return (0);
	}
#endif
	pcb->pcb_fsbase = (register_t)tls_base;
	return (0);
}