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
struct thread {TYPE_2__* td_pcb; TYPE_1__* td_frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcb_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  tf_spsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_SINGLE_STEP ; 
 int /*<<< orphan*/  PSR_SS ; 

int
ptrace_single_step(struct thread *td)
{

	td->td_frame->tf_spsr |= PSR_SS;
	td->td_pcb->pcb_flags |= PCB_SINGLE_STEP;
	return (0);
}