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
struct vmci_softc {int capabilities; int /*<<< orphan*/  vmci_ioh0; int /*<<< orphan*/  vmci_iot0; int /*<<< orphan*/  vmci_intr_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int VMCI_CAPS_NOTIFICATIONS ; 
 int /*<<< orphan*/  VMCI_CONTROL_ADDR ; 
 int VMCI_CONTROL_INT_ENABLE ; 
 int /*<<< orphan*/  VMCI_IMR_ADDR ; 
 int VMCI_IMR_DATAGRAM ; 
 int VMCI_IMR_NOTIFICATION ; 
 int /*<<< orphan*/  VMCI_INTR_TYPE_INTX ; 
 int /*<<< orphan*/  VMCI_INTR_TYPE_MSI ; 
 int /*<<< orphan*/  VMCI_INTR_TYPE_MSIX ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * data_buffer ; 
 int /*<<< orphan*/  data_buffer_size ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vmci_config_interrupt (struct vmci_softc*) ; 

__attribute__((used)) static int
vmci_config_interrupts(struct vmci_softc *sc)
{
	int error;

	data_buffer = malloc(data_buffer_size, M_DEVBUF, M_ZERO | M_NOWAIT);
	if (data_buffer == NULL)
		return (ENOMEM);

	sc->vmci_intr_type = VMCI_INTR_TYPE_MSIX;
	error = vmci_config_interrupt(sc);
	if (error) {
		sc->vmci_intr_type = VMCI_INTR_TYPE_MSI;
		error = vmci_config_interrupt(sc);
	}
	if (error) {
		sc->vmci_intr_type = VMCI_INTR_TYPE_INTX;
		error = vmci_config_interrupt(sc);
	}
	if (error)
		return (error);

	/* Enable specific interrupt bits. */
	if (sc->capabilities & VMCI_CAPS_NOTIFICATIONS)
		bus_space_write_4(sc->vmci_iot0, sc->vmci_ioh0,
		    VMCI_IMR_ADDR, VMCI_IMR_DATAGRAM | VMCI_IMR_NOTIFICATION);
	else
		bus_space_write_4(sc->vmci_iot0, sc->vmci_ioh0,
		    VMCI_IMR_ADDR, VMCI_IMR_DATAGRAM);

	/* Enable interrupts. */
	bus_space_write_4(sc->vmci_iot0, sc->vmci_ioh0,
	    VMCI_CONTROL_ADDR, VMCI_CONTROL_INT_ENABLE);

	return (0);
}