#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* md_tp; } ;
struct thread {TYPE_3__ td_md; TYPE_2__* td_pcb; } ;
typedef  void* register_t ;
struct TYPE_4__ {void* sf_tpidrurw; } ;
struct TYPE_5__ {TYPE_1__ pcb_regs; } ;

/* Variables and functions */
 scalar_t__ ARM_TP_ADDRESS ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  set_tls (void*) ; 

int
cpu_set_user_tls(struct thread *td, void *tls_base)
{

#if __ARM_ARCH >= 6
	td->td_pcb->pcb_regs.sf_tpidrurw = (register_t)tls_base;
	if (td == curthread)
		set_tls(tls_base);
#else
	td->td_md.md_tp = (register_t)tls_base;
	if (td == curthread) {
		critical_enter();
		*(register_t *)ARM_TP_ADDRESS = (register_t)tls_base;
		critical_exit();
	}
#endif
	return (0);
}