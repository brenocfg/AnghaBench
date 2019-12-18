#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_6__ {int td_pflags; } ;
struct TYPE_5__ {scalar_t__ pcb_save; int /*<<< orphan*/  pcb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PCB_KERNNPX ; 
 int PCB_USER_FPU (TYPE_1__*) ; 
 int TDP_KTHREAD ; 
 TYPE_1__* curpcb ; 
 TYPE_2__* curthread ; 
 scalar_t__ get_pcb_user_save_pcb (TYPE_1__*) ; 

int
fpu_kern_thread(u_int flags)
{

	KASSERT((curthread->td_pflags & TDP_KTHREAD) != 0,
	    ("Only kthread may use fpu_kern_thread"));
	KASSERT(curpcb->pcb_save == get_pcb_user_save_pcb(curpcb),
	    ("mangled pcb_save"));
	KASSERT(PCB_USER_FPU(curpcb), ("recursive call"));

	curpcb->pcb_flags |= PCB_KERNNPX;
	return (0);
}