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
typedef  scalar_t__ uint64_t ;
struct thread {TYPE_1__* td_frame; struct pcb* td_pcb; } ;
struct pcb {scalar_t__ pcb_fsbase; } ;
typedef  scalar_t__ register_t ;
struct TYPE_2__ {int /*<<< orphan*/  tf_fs; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  _ufssel ; 

int
linux_set_cloned_tls(struct thread *td, void *desc)
{
	struct pcb *pcb;

	if ((uint64_t)desc >= VM_MAXUSER_ADDRESS)
		return (EPERM);

	pcb = td->td_pcb;
	pcb->pcb_fsbase = (register_t)desc;
	td->td_frame->tf_fs = _ufssel;

	return (0);
}