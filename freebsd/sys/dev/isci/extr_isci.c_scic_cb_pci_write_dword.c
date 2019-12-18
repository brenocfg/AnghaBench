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
typedef  size_t uint32_t ;
struct isci_softc {TYPE_1__* pci_bar; } ;
struct ISCI_CONTROLLER {struct isci_softc* isci; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus_handle; int /*<<< orphan*/  bus_tag; } ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int POINTER_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 

void
scic_cb_pci_write_dword(SCI_CONTROLLER_HANDLE_T scic_controller,
    void *address, uint32_t write_value)
{
	SCI_CONTROLLER_HANDLE_T scif_controller =
	    (SCI_CONTROLLER_HANDLE_T) sci_object_get_association(scic_controller);
	struct ISCI_CONTROLLER *isci_controller =
	    (struct ISCI_CONTROLLER *) sci_object_get_association(scif_controller);
	struct isci_softc *isci = isci_controller->isci;
	uint32_t bar = (uint32_t)(((POINTER_UINT)address & 0xF0000000) >> 28);
	bus_size_t offset = (bus_size_t)((POINTER_UINT)address & 0x0FFFFFFF);

	bus_space_write_4(isci->pci_bar[bar].bus_tag,
	    isci->pci_bar[bar].bus_handle, offset, write_value);
}