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
struct pcb {void* pcb_tpidr_el0; void* pcb_tpidrro_el0; } ;
typedef  void* register_t ;
struct TYPE_2__ {int tf_spsr; } ;

/* Variables and functions */
 int EINVAL ; 
 int PSR_M_32 ; 
 uintptr_t VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  WRITE_SPECIALREG (int /*<<< orphan*/ ,void*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  tpidr_el0 ; 
 int /*<<< orphan*/  tpidrro_el0 ; 

int
cpu_set_user_tls(struct thread *td, void *tls_base)
{
	struct pcb *pcb;

	if ((uintptr_t)tls_base >= VM_MAXUSER_ADDRESS)
		return (EINVAL);

	pcb = td->td_pcb;
	if (td->td_frame->tf_spsr & PSR_M_32) {
		/* 32bits arm stores the user TLS into tpidrro */
		pcb->pcb_tpidrro_el0 = (register_t)tls_base;
		pcb->pcb_tpidr_el0 = (register_t)tls_base;
		if (td == curthread) {
			WRITE_SPECIALREG(tpidrro_el0, tls_base);
			WRITE_SPECIALREG(tpidr_el0, tls_base);
		}
	} else {
		pcb->pcb_tpidr_el0 = (register_t)tls_base;
		if (td == curthread)
			WRITE_SPECIALREG(tpidr_el0, tls_base);
	}

	return (0);
}