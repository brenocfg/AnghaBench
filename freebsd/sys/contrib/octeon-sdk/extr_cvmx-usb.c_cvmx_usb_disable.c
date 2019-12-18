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
typedef  int /*<<< orphan*/  cvmx_usb_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ cvmx_usb_internal_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_HPRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CVMX_USB_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USB_SUCCESS ; 
 int /*<<< orphan*/  USB_SET_FIELD32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvmx_usbcx_hprt_t ; 
 int /*<<< orphan*/  prtena ; 

cvmx_usb_status_t cvmx_usb_disable(cvmx_usb_state_t *state)
{
    cvmx_usb_internal_state_t *usb = (cvmx_usb_internal_state_t*)state;

    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", state);

    /* Disable the port */
    USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index), cvmx_usbcx_hprt_t, prtena, 1);
    CVMX_USB_RETURN(CVMX_USB_SUCCESS);
}