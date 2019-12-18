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
typedef  int /*<<< orphan*/  cvmx_usb_status_t ;
typedef  void cvmx_usb_state_t ;
struct TYPE_2__ {void** callback_data; void** callback; } ;
typedef  TYPE_1__ cvmx_usb_internal_state_t ;
typedef  size_t cvmx_usb_callback_t ;
typedef  void* cvmx_usb_callback_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,void*) ; 
 int /*<<< orphan*/  CVMX_USB_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USB_SUCCESS ; 
 size_t __CVMX_USB_CALLBACK_END ; 
 scalar_t__ cvmx_unlikely (int) ; 

cvmx_usb_status_t cvmx_usb_register_callback(cvmx_usb_state_t *state,
                                             cvmx_usb_callback_t reason,
                                             cvmx_usb_callback_func_t callback,
                                             void *user_data)
{
    cvmx_usb_internal_state_t *usb = (cvmx_usb_internal_state_t*)state;

    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", state);
    CVMX_USB_LOG_PARAM("%d", reason);
    CVMX_USB_LOG_PARAM("%p", callback);
    CVMX_USB_LOG_PARAM("%p", user_data);
    if (cvmx_unlikely(reason >= __CVMX_USB_CALLBACK_END))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(!callback))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);

    usb->callback[reason] = callback;
    usb->callback_data[reason] = user_data;

    CVMX_USB_RETURN(CVMX_USB_SUCCESS);
}