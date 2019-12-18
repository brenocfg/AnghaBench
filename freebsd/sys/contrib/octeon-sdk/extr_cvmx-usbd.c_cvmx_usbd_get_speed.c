#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ cvmx_usbd_state_t ;
typedef  int /*<<< orphan*/  cvmx_usbd_speed_t ;
struct TYPE_6__ {int /*<<< orphan*/  enumspd; } ;
struct TYPE_8__ {TYPE_1__ s; int /*<<< orphan*/  u32; } ;
typedef  TYPE_3__ cvmx_usbcx_dsts_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_DSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_usbd_read_csr32 (TYPE_2__*,int /*<<< orphan*/ ) ; 

cvmx_usbd_speed_t cvmx_usbd_get_speed(cvmx_usbd_state_t *usb)
{
    cvmx_usbcx_dsts_t usbcx_dsts;
    usbcx_dsts.u32 = __cvmx_usbd_read_csr32(usb, CVMX_USBCX_DSTS(usb->index));
    return usbcx_dsts.s.enumspd;
}