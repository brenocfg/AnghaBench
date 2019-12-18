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
struct octusb_td {int error_any; int error_stall; TYPE_1__* qh; } ;
typedef  int /*<<< orphan*/  cvmx_usb_state_t ;
typedef  int cvmx_usb_complete_t ;
typedef  scalar_t__ cvmx_usb_callback_t ;
struct TYPE_2__ {int fixup_complete; int fixup_actlen; int fixup_handle; scalar_t__ fixup_pending; } ;

/* Variables and functions */
 scalar_t__ CVMX_USB_CALLBACK_TRANSFER_COMPLETE ; 
#define  CVMX_USB_COMPLETE_SHORT 130 
#define  CVMX_USB_COMPLETE_STALL 129 
#define  CVMX_USB_COMPLETE_SUCCESS 128 

__attribute__((used)) static void
octusb_complete_cb(cvmx_usb_state_t *state,
    cvmx_usb_callback_t reason,
    cvmx_usb_complete_t status,
    int pipe_handle, int submit_handle,
    int bytes_transferred, void *user_data)
{
	struct octusb_td *td;

	if (reason != CVMX_USB_CALLBACK_TRANSFER_COMPLETE)
		return;

	td = user_data;

	td->qh->fixup_complete = 1;
	td->qh->fixup_pending = 0;
	td->qh->fixup_actlen = bytes_transferred;
	td->qh->fixup_handle = -1;

	switch (status) {
	case CVMX_USB_COMPLETE_SUCCESS:
	case CVMX_USB_COMPLETE_SHORT:
		td->error_any = 0;
		td->error_stall = 0;
		break;
	case CVMX_USB_COMPLETE_STALL:
		td->error_stall = 1;
		td->error_any = 1;
		break;
	default:
		td->error_any = 1;
		break;
	}
}