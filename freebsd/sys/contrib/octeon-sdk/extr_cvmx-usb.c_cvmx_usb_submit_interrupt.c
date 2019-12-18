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
typedef  int /*<<< orphan*/  cvmx_usb_internal_state_t ;
typedef  int /*<<< orphan*/  cvmx_usb_callback_func_t ;

/* Variables and functions */
 int CVMX_USB_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_USB_RETURN (int) ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_INTERRUPT ; 
 int __cvmx_usb_submit_transaction (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ cvmx_unlikely (int) ; 

int cvmx_usb_submit_interrupt(cvmx_usb_state_t *state, int pipe_handle,
                              uint64_t buffer, int buffer_length,
                              cvmx_usb_callback_func_t callback,
                              void *user_data)
{
    int submit_handle;
    cvmx_usb_internal_state_t *usb = (cvmx_usb_internal_state_t*)state;

    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", state);
    CVMX_USB_LOG_PARAM("%d", pipe_handle);
    CVMX_USB_LOG_PARAM("0x%llx", (unsigned long long)buffer);
    CVMX_USB_LOG_PARAM("%d", buffer_length);

    /* Pipe handle checking is done later in a common place */
    if (cvmx_unlikely(!buffer))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(buffer_length < 0))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);

    submit_handle = __cvmx_usb_submit_transaction(usb, pipe_handle,
                                         CVMX_USB_TRANSFER_INTERRUPT,
                                         0, /* flags */
                                         buffer,
                                         buffer_length,
                                         0, /* control_header */
                                         0, /* iso_start_frame */
                                         0, /* iso_number_packets */
                                         NULL, /* iso_packets */
                                         callback,
                                         user_data);
    CVMX_USB_RETURN(submit_handle);
}