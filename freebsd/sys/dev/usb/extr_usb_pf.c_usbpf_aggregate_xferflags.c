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
struct usb_xfer_flags {int force_short_xfer; int short_xfer_ok; int short_frames_ok; int pipe_bof; int proxy_buffer; int ext_buffer; int manual_status; int no_pipe_ok; int stall_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBPF_FLAG_EXT_BUFFER ; 
 int /*<<< orphan*/  USBPF_FLAG_FORCE_SHORT_XFER ; 
 int /*<<< orphan*/  USBPF_FLAG_MANUAL_STATUS ; 
 int /*<<< orphan*/  USBPF_FLAG_NO_PIPE_OK ; 
 int /*<<< orphan*/  USBPF_FLAG_PIPE_BOF ; 
 int /*<<< orphan*/  USBPF_FLAG_PROXY_BUFFER ; 
 int /*<<< orphan*/  USBPF_FLAG_SHORT_FRAMES_OK ; 
 int /*<<< orphan*/  USBPF_FLAG_SHORT_XFER_OK ; 
 int /*<<< orphan*/  USBPF_FLAG_STALL_PIPE ; 

__attribute__((used)) static uint32_t
usbpf_aggregate_xferflags(struct usb_xfer_flags *flags)
{
	uint32_t val = 0;

	if (flags->force_short_xfer == 1)
		val |= USBPF_FLAG_FORCE_SHORT_XFER;
	if (flags->short_xfer_ok == 1)
		val |= USBPF_FLAG_SHORT_XFER_OK;
	if (flags->short_frames_ok == 1)
		val |= USBPF_FLAG_SHORT_FRAMES_OK;
	if (flags->pipe_bof == 1)
		val |= USBPF_FLAG_PIPE_BOF;
	if (flags->proxy_buffer == 1)
		val |= USBPF_FLAG_PROXY_BUFFER;
	if (flags->ext_buffer == 1)
		val |= USBPF_FLAG_EXT_BUFFER;
	if (flags->manual_status == 1)
		val |= USBPF_FLAG_MANUAL_STATUS;
	if (flags->no_pipe_ok == 1)
		val |= USBPF_FLAG_NO_PIPE_OK;
	if (flags->stall_pipe == 1)
		val |= USBPF_FLAG_STALL_PIPE;
	return (val);
}