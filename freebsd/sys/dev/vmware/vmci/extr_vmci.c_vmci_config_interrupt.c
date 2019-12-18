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
struct vmci_softc {int dummy; } ;

/* Variables and functions */
 int vmci_allocate_interrupt_resources (struct vmci_softc*) ; 
 int vmci_check_intr_cnt (struct vmci_softc*) ; 
 int vmci_setup_interrupts (struct vmci_softc*) ; 

__attribute__((used)) static int
vmci_config_interrupt(struct vmci_softc *sc)
{
	int error;

	error = vmci_check_intr_cnt(sc);
	if (error)
		return (error);

	error = vmci_allocate_interrupt_resources(sc);
	if (error)
		return (error);

	error = vmci_setup_interrupts(sc);
	if (error)
		return (error);

	return (0);
}