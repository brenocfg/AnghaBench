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
struct TYPE_2__ {int vmci_num_intr; int /*<<< orphan*/  vmci_interrupt_bm_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 
 TYPE_1__* vmci_sc ; 

__attribute__((used)) static void
vmci_interrupt_bm(void *arg)
{

	ASSERT(vmci_sc->vmci_num_intr == 2);
	taskqueue_enqueue(taskqueue_swi, &vmci_sc->vmci_interrupt_bm_task);
}