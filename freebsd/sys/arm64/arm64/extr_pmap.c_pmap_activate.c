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
struct thread {TYPE_1__* td_proc; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  pmap_activate_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 

void
pmap_activate(struct thread *td)
{
	pmap_t	pmap;

	pmap = vmspace_pmap(td->td_proc->p_vmspace);
	critical_enter();
	(void)pmap_activate_int(pmap);
	critical_exit();
}