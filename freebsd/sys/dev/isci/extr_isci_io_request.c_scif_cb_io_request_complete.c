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
struct ISCI_IO_REQUEST {int dummy; } ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_IO_STATUS ;
typedef  int /*<<< orphan*/  SCI_IO_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  isci_io_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ISCI_IO_REQUEST*,int /*<<< orphan*/ ) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_complete_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scif_cb_io_request_complete(SCI_CONTROLLER_HANDLE_T scif_controller,
    SCI_REMOTE_DEVICE_HANDLE_T remote_device,
    SCI_IO_REQUEST_HANDLE_T io_request, SCI_IO_STATUS completion_status)
{
	struct ISCI_IO_REQUEST *isci_request =
	    (struct ISCI_IO_REQUEST *)sci_object_get_association(io_request);

	scif_controller_complete_io(scif_controller, remote_device, io_request);
	isci_io_request_complete(scif_controller, remote_device, isci_request,
	    completion_status);
}