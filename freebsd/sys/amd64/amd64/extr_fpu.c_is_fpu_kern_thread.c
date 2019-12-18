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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int pcb_flags; } ;
struct TYPE_3__ {int td_pflags; } ;

/* Variables and functions */
 int PCB_KERNFPU ; 
 int TDP_KTHREAD ; 
 TYPE_2__* curpcb ; 
 TYPE_1__* curthread ; 

int
is_fpu_kern_thread(u_int flags)
{

	if ((curthread->td_pflags & TDP_KTHREAD) == 0)
		return (0);
	return ((curpcb->pcb_flags & PCB_KERNFPU) != 0);
}