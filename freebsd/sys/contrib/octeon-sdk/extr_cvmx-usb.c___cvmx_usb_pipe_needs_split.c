#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ device_speed; } ;
typedef  TYPE_3__ cvmx_usb_pipe_t ;
struct TYPE_7__ {scalar_t__ prtspd; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_10__ {TYPE_2__ usbcx_hprt; } ;
typedef  TYPE_4__ cvmx_usb_internal_state_t ;

/* Variables and functions */
 scalar_t__ CVMX_USB_SPEED_HIGH ; 

__attribute__((used)) static inline int __cvmx_usb_pipe_needs_split(cvmx_usb_internal_state_t *usb, cvmx_usb_pipe_t *pipe)
{
    return ((pipe->device_speed != CVMX_USB_SPEED_HIGH) && (usb->usbcx_hprt.s.prtspd == CVMX_USB_SPEED_HIGH));
}