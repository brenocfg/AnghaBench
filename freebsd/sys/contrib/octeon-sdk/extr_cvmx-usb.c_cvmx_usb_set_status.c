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
typedef  int /*<<< orphan*/  cvmx_usb_state_t ;
typedef  int /*<<< orphan*/  cvmx_usb_port_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  port_status; } ;
typedef  TYPE_1__ cvmx_usb_internal_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CVMX_USB_RETURN_NOTHING () ; 

void cvmx_usb_set_status(cvmx_usb_state_t *state, cvmx_usb_port_status_t port_status)
{
    cvmx_usb_internal_state_t *usb = (cvmx_usb_internal_state_t*)state;
    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", state);
    usb->port_status = port_status;
    CVMX_USB_RETURN_NOTHING();
}