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
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_xfer_flags_int {int open; int transferring; int did_dma_delay; int did_close; int draining; int started; int bandwidth_reclaimed; int control_xfr; int control_hdr; int control_act; int control_stall; int short_frames_ok; int short_xfer_ok; int bdma_enable; int bdma_no_post_sync; int bdma_setup; int isochronous_xfr; int curr_dma_set; int can_cancel_immed; int doing_callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBPF_STATUS_BDMA_ENABLE ; 
 int /*<<< orphan*/  USBPF_STATUS_BDMA_NO_POST_SYNC ; 
 int /*<<< orphan*/  USBPF_STATUS_BDMA_SETUP ; 
 int /*<<< orphan*/  USBPF_STATUS_BW_RECLAIMED ; 
 int /*<<< orphan*/  USBPF_STATUS_CAN_CANCEL_IMMED ; 
 int /*<<< orphan*/  USBPF_STATUS_CONTROL_ACT ; 
 int /*<<< orphan*/  USBPF_STATUS_CONTROL_HDR ; 
 int /*<<< orphan*/  USBPF_STATUS_CONTROL_STALL ; 
 int /*<<< orphan*/  USBPF_STATUS_CONTROL_XFR ; 
 int /*<<< orphan*/  USBPF_STATUS_CURR_DMA_SET ; 
 int /*<<< orphan*/  USBPF_STATUS_DID_CLOSE ; 
 int /*<<< orphan*/  USBPF_STATUS_DID_DMA_DELAY ; 
 int /*<<< orphan*/  USBPF_STATUS_DOING_CALLBACK ; 
 int /*<<< orphan*/  USBPF_STATUS_DRAINING ; 
 int /*<<< orphan*/  USBPF_STATUS_ISOCHRONOUS_XFR ; 
 int /*<<< orphan*/  USBPF_STATUS_OPEN ; 
 int /*<<< orphan*/  USBPF_STATUS_SHORT_FRAMES_OK ; 
 int /*<<< orphan*/  USBPF_STATUS_SHORT_XFER_OK ; 
 int /*<<< orphan*/  USBPF_STATUS_STARTED ; 
 int /*<<< orphan*/  USBPF_STATUS_TRANSFERRING ; 

__attribute__((used)) static uint32_t
usbpf_aggregate_status(struct usb_xfer_flags_int *flags)
{
	uint32_t val = 0;

	if (flags->open == 1)
		val |= USBPF_STATUS_OPEN;
	if (flags->transferring == 1)
		val |= USBPF_STATUS_TRANSFERRING;
	if (flags->did_dma_delay == 1)
		val |= USBPF_STATUS_DID_DMA_DELAY;
	if (flags->did_close == 1)
		val |= USBPF_STATUS_DID_CLOSE;
	if (flags->draining == 1)
		val |= USBPF_STATUS_DRAINING;
	if (flags->started == 1)
		val |= USBPF_STATUS_STARTED;
	if (flags->bandwidth_reclaimed == 1)
		val |= USBPF_STATUS_BW_RECLAIMED;
	if (flags->control_xfr == 1)
		val |= USBPF_STATUS_CONTROL_XFR;
	if (flags->control_hdr == 1)
		val |= USBPF_STATUS_CONTROL_HDR;
	if (flags->control_act == 1)
		val |= USBPF_STATUS_CONTROL_ACT;
	if (flags->control_stall == 1)
		val |= USBPF_STATUS_CONTROL_STALL;
	if (flags->short_frames_ok == 1)
		val |= USBPF_STATUS_SHORT_FRAMES_OK;
	if (flags->short_xfer_ok == 1)
		val |= USBPF_STATUS_SHORT_XFER_OK;
#if USB_HAVE_BUSDMA
	if (flags->bdma_enable == 1)
		val |= USBPF_STATUS_BDMA_ENABLE;
	if (flags->bdma_no_post_sync == 1)
		val |= USBPF_STATUS_BDMA_NO_POST_SYNC;
	if (flags->bdma_setup == 1)
		val |= USBPF_STATUS_BDMA_SETUP;
#endif
	if (flags->isochronous_xfr == 1)
		val |= USBPF_STATUS_ISOCHRONOUS_XFR;
	if (flags->curr_dma_set == 1)
		val |= USBPF_STATUS_CURR_DMA_SET;
	if (flags->can_cancel_immed == 1)
		val |= USBPF_STATUS_CAN_CANCEL_IMMED;
	if (flags->doing_callback == 1)
		val |= USBPF_STATUS_DOING_CALLBACK;

	return (val);
}