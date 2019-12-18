#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ISCI_IO_REQUEST {TYPE_2__* ccb; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  SCI_IO_REQUEST_DATA_DIRECTION ;

/* Variables and functions */
#define  CAM_DIR_IN 129 
 int CAM_DIR_MASK ; 
#define  CAM_DIR_OUT 128 
 int /*<<< orphan*/  SCI_IO_REQUEST_DATA_IN ; 
 int /*<<< orphan*/  SCI_IO_REQUEST_DATA_OUT ; 
 int /*<<< orphan*/  SCI_IO_REQUEST_NO_DATA ; 

SCI_IO_REQUEST_DATA_DIRECTION
scif_cb_io_request_get_data_direction(void * scif_user_io_request)
{
	struct ISCI_IO_REQUEST *isci_request =
	    (struct ISCI_IO_REQUEST *)scif_user_io_request;

	switch (isci_request->ccb->ccb_h.flags & CAM_DIR_MASK) {
	case CAM_DIR_IN:
		return (SCI_IO_REQUEST_DATA_IN);
	case CAM_DIR_OUT:
		return (SCI_IO_REQUEST_DATA_OUT);
	default:
		return (SCI_IO_REQUEST_NO_DATA);
	}
}