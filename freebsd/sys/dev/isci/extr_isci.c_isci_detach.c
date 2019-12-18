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
struct isci_softc {int controller_count; int num_interrupts; struct ISCI_INTERRUPT_INFO* interrupt_info; struct ISCI_PCI_BAR* pci_bar; int /*<<< orphan*/ * sci_library_memory; struct ISCI_CONTROLLER* controllers; } ;
struct ISCI_PCI_BAR {int /*<<< orphan*/ * resource; int /*<<< orphan*/  resource_id; } ;
struct ISCI_INTERRUPT_INFO {int /*<<< orphan*/ * res; int /*<<< orphan*/ * tag; } ;
struct ISCI_CONTROLLER {scalar_t__ is_started; int /*<<< orphan*/  unmap_buffer_pool; TYPE_1__* phys; int /*<<< orphan*/ * remote_device_memory; int /*<<< orphan*/ * timer_memory; int /*<<< orphan*/  lock; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/ * scif_controller_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ cdev_locate; scalar_t__ cdev_fault; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;

/* Variables and functions */
 struct isci_softc* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 int ISCI_NUM_PCI_BARS ; 
 int /*<<< orphan*/  M_ISCI ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SCI_MAX_PHYS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  contigfree (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_interrupt_poll_handler (struct ISCI_CONTROLLER*) ; 
 int /*<<< orphan*/  led_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_pool_get (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  scic_controller_disable_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_get_scic_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_controller_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isci_detach(device_t device)
{
	struct isci_softc *isci = DEVICE2SOFTC(device);
	int i, phy;

	for (i = 0; i < isci->controller_count; i++) {
		struct ISCI_CONTROLLER *controller = &isci->controllers[i];
		SCI_STATUS status;
		void *unmap_buffer;

		if (controller->scif_controller_handle != NULL) {
			scic_controller_disable_interrupts(
			    scif_controller_get_scic_handle(controller->scif_controller_handle));

			mtx_lock(&controller->lock);
			status = scif_controller_stop(controller->scif_controller_handle, 0);
			mtx_unlock(&controller->lock);

			while (controller->is_started == TRUE) {
				/* Now poll for interrupts until the controller stop complete
				 *  callback is received.
				 */
				mtx_lock(&controller->lock);
				isci_interrupt_poll_handler(controller);
				mtx_unlock(&controller->lock);
				pause("isci", 1);
			}

			if(controller->sim != NULL) {
				mtx_lock(&controller->lock);
				xpt_free_path(controller->path);
				xpt_bus_deregister(cam_sim_path(controller->sim));
				cam_sim_free(controller->sim, TRUE);
				mtx_unlock(&controller->lock);
			}
		}

		if (controller->timer_memory != NULL)
			free(controller->timer_memory, M_ISCI);

		if (controller->remote_device_memory != NULL)
			free(controller->remote_device_memory, M_ISCI);

		for (phy = 0; phy < SCI_MAX_PHYS; phy++) {
			if (controller->phys[phy].cdev_fault)
				led_destroy(controller->phys[phy].cdev_fault);

			if (controller->phys[phy].cdev_locate)
				led_destroy(controller->phys[phy].cdev_locate);
		}

		while (1) {
			sci_pool_get(controller->unmap_buffer_pool, unmap_buffer);
			if (unmap_buffer == NULL)
				break;
			contigfree(unmap_buffer, PAGE_SIZE, M_ISCI);
		}
	}

	/* The SCIF controllers have been stopped, so we can now
	 *  free the SCI library memory.
	 */
	if (isci->sci_library_memory != NULL)
		free(isci->sci_library_memory, M_ISCI);

	for (i = 0; i < ISCI_NUM_PCI_BARS; i++)
	{
		struct ISCI_PCI_BAR *pci_bar = &isci->pci_bar[i];

		if (pci_bar->resource != NULL)
			bus_release_resource(device, SYS_RES_MEMORY,
			    pci_bar->resource_id, pci_bar->resource);
	}

	for (i = 0; i < isci->num_interrupts; i++)
	{
		struct ISCI_INTERRUPT_INFO *interrupt_info;

		interrupt_info = &isci->interrupt_info[i];

		if(interrupt_info->tag != NULL)
			bus_teardown_intr(device, interrupt_info->res,
			    interrupt_info->tag);

		if(interrupt_info->res != NULL)
			bus_release_resource(device, SYS_RES_IRQ,
			    rman_get_rid(interrupt_info->res),
			    interrupt_info->res);

		pci_release_msi(device);
	}
	pci_disable_busmaster(device);

	return (0);
}