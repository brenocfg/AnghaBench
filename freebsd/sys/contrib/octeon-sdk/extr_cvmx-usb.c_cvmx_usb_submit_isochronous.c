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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cvmx_usb_state_t ;
typedef  int /*<<< orphan*/  cvmx_usb_iso_packet_t ;
typedef  int /*<<< orphan*/  cvmx_usb_internal_state_t ;
typedef  int /*<<< orphan*/  cvmx_usb_callback_func_t ;

/* Variables and functions */
 int CVMX_USB_INVALID_PARAM ; 
 int CVMX_USB_ISOCHRONOUS_FLAGS_ALLOW_SHORT ; 
 int CVMX_USB_ISOCHRONOUS_FLAGS_ASAP ; 
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_USB_RETURN (int) ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_ISOCHRONOUS ; 
 int __cvmx_usb_submit_transaction (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ cvmx_unlikely (int) ; 

int cvmx_usb_submit_isochronous(cvmx_usb_state_t *state, int pipe_handle,
                                int start_frame, int flags,
                                int number_packets,
                                cvmx_usb_iso_packet_t packets[],
                                uint64_t buffer, int buffer_length,
                                cvmx_usb_callback_func_t callback,
                                void *user_data)
{
    int submit_handle;
    cvmx_usb_internal_state_t *usb = (cvmx_usb_internal_state_t*)state;

    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", state);
    CVMX_USB_LOG_PARAM("%d", pipe_handle);
    CVMX_USB_LOG_PARAM("%d", start_frame);
    CVMX_USB_LOG_PARAM("0x%x", flags);
    CVMX_USB_LOG_PARAM("%d", number_packets);
    CVMX_USB_LOG_PARAM("%p", packets);
    CVMX_USB_LOG_PARAM("0x%llx", (unsigned long long)buffer);
    CVMX_USB_LOG_PARAM("%d", buffer_length);

    /* Pipe handle checking is done later in a common place */
    if (cvmx_unlikely(start_frame < 0))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(flags & ~(CVMX_USB_ISOCHRONOUS_FLAGS_ALLOW_SHORT | CVMX_USB_ISOCHRONOUS_FLAGS_ASAP)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(number_packets < 1))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(!packets))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(!buffer))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(buffer_length < 0))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);

    submit_handle = __cvmx_usb_submit_transaction(usb, pipe_handle,
                                         CVMX_USB_TRANSFER_ISOCHRONOUS,
                                         flags,
                                         buffer,
                                         buffer_length,
                                         0, /* control_header */
                                         start_frame,
                                         number_packets,
                                         packets,
                                         callback,
                                         user_data);
    CVMX_USB_RETURN(submit_handle);
}