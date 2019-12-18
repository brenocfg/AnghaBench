#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ISCI_CONTROLLER {int /*<<< orphan*/  unmap_buffer_pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  virtual_address; } ;
typedef  TYPE_1__ SCI_PHYSICAL_MEMORY_DESCRIPTOR_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scif_cb_controller_free_memory(SCI_CONTROLLER_HANDLE_T controller,
    SCI_PHYSICAL_MEMORY_DESCRIPTOR_T * mde)
{
	struct ISCI_CONTROLLER *isci_controller = (struct ISCI_CONTROLLER *)
	    sci_object_get_association(controller);

	/*
	 * Put the buffer back into the controller's buffer pool, rather
	 * than invoking configfree.  This helps reduce chance we won't
	 * have buffers available when system is under memory pressure.
	 */ 
	sci_pool_put(isci_controller->unmap_buffer_pool,
	    mde->virtual_address);
}