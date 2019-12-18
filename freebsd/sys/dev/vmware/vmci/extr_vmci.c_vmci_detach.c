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
struct TYPE_2__ {int /*<<< orphan*/ * dma_vaddr; } ;
struct vmci_softc {int /*<<< orphan*/  vmci_spinlock; TYPE_1__ vmci_notifications_bitmap; int /*<<< orphan*/  vmci_ioh0; int /*<<< orphan*/  vmci_iot0; int /*<<< orphan*/ * vmci_res0; int /*<<< orphan*/  vmci_delayed_work_lock; int /*<<< orphan*/  vmci_delayed_work_task; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_CONTROL_ADDR ; 
 int /*<<< orphan*/  VMCI_CONTROL_RESET ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  vmci_components_cleanup () ; 
 int /*<<< orphan*/  vmci_dismantle_interrupts (struct vmci_softc*) ; 
 int /*<<< orphan*/  vmci_dma_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vmci_qp_guest_endpoints_exit () ; 
 int /*<<< orphan*/  vmci_unmap_bars (struct vmci_softc*) ; 
 int /*<<< orphan*/  vmci_util_exit () ; 

__attribute__((used)) static int
vmci_detach(device_t dev)
{
	struct vmci_softc *sc;

	sc = device_get_softc(dev);

	vmci_qp_guest_endpoints_exit();
	vmci_util_exit();

	vmci_dismantle_interrupts(sc);

	vmci_components_cleanup();

	taskqueue_drain(taskqueue_thread, &sc->vmci_delayed_work_task);
	mtx_destroy(&sc->vmci_delayed_work_lock);

	if (sc->vmci_res0 != NULL)
		bus_space_write_4(sc->vmci_iot0, sc->vmci_ioh0,
		    VMCI_CONTROL_ADDR, VMCI_CONTROL_RESET);

	if (sc->vmci_notifications_bitmap.dma_vaddr != NULL)
		vmci_dma_free(&sc->vmci_notifications_bitmap);

	vmci_unmap_bars(sc);

	mtx_destroy(&sc->vmci_spinlock);

	pci_disable_busmaster(dev);

	return (0);
}