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
struct ISCI_REQUEST {scalar_t__ physical_address; } ;
struct TYPE_2__ {scalar_t__ physical_address; scalar_t__ virtual_address; } ;
struct ISCI_CONTROLLER {TYPE_1__ uncached_controller_memory; } ;
typedef  scalar_t__ U64 ;
typedef  scalar_t__ SCI_PHYSICAL_ADDRESS ;
typedef  void* SCI_IO_REQUEST_HANDLE_T ;
typedef  void* SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 void* sci_object_get_association (void*) ; 

void
scic_cb_io_request_get_physical_address(SCI_CONTROLLER_HANDLE_T	controller,
    SCI_IO_REQUEST_HANDLE_T io_request, void *virtual_address,
    SCI_PHYSICAL_ADDRESS *physical_address)
{
	SCI_IO_REQUEST_HANDLE_T scif_request =
	    sci_object_get_association(io_request);
	struct ISCI_REQUEST *isci_request =
	    sci_object_get_association(scif_request);

	if(isci_request != NULL) {
		/* isci_request is not NULL, meaning this is a request initiated
		 *  by CAM or the isci layer (i.e. device reset for I/O
		 *  timeout).  Therefore we can calculate the physical address
		 *  based on the address we stored in the struct ISCI_REQUEST
		 *  object.
		 */
		*physical_address = isci_request->physical_address +
		    (uintptr_t)virtual_address -
		    (uintptr_t)isci_request;
	} else {
		/* isci_request is NULL, meaning this is a request generated
		 *  internally by SCIL (i.e. for SMP requests or NCQ error
		 *  recovery).  Therefore we calculate the physical address
		 *  based on the controller's uncached controller memory buffer,
		 *  since we know that this is what SCIL uses for internal
		 *  framework requests.
		 */
		SCI_CONTROLLER_HANDLE_T scif_controller =
		    (SCI_CONTROLLER_HANDLE_T) sci_object_get_association(controller);
		struct ISCI_CONTROLLER *isci_controller =
		    (struct ISCI_CONTROLLER *)sci_object_get_association(scif_controller);
		U64 virt_addr_offset = (uintptr_t)virtual_address -
		    (U64)isci_controller->uncached_controller_memory.virtual_address;

		*physical_address =
		    isci_controller->uncached_controller_memory.physical_address
		    + virt_addr_offset;
	}
}