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
struct TYPE_2__ {scalar_t__ pin; scalar_t__ state; int /*<<< orphan*/  lock; } ;
struct pci_devinst {TYPE_1__ pi_lintr; } ;

/* Variables and functions */
 scalar_t__ ASSERTED ; 
 scalar_t__ IDLE ; 
 scalar_t__ PENDING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pci_irq_assert (struct pci_devinst*) ; 
 scalar_t__ pci_lintr_permitted (struct pci_devinst*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
pci_lintr_assert(struct pci_devinst *pi)
{

	assert(pi->pi_lintr.pin > 0);

	pthread_mutex_lock(&pi->pi_lintr.lock);
	if (pi->pi_lintr.state == IDLE) {
		if (pci_lintr_permitted(pi)) {
			pi->pi_lintr.state = ASSERTED;
			pci_irq_assert(pi);
		} else
			pi->pi_lintr.state = PENDING;
	}
	pthread_mutex_unlock(&pi->pi_lintr.lock);
}