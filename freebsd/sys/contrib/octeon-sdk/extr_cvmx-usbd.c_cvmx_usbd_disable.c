#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ cvmx_usbd_state_t ;
struct TYPE_7__ {int sgoutnak; int sftdiscon; } ;
struct TYPE_9__ {int /*<<< orphan*/  u32; TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_usbcx_dctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_DCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_usbd_read_csr32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_usbd_write_csr32 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cvmx_usbd_disable(cvmx_usbd_state_t *usb)
{
    cvmx_usbcx_dctl_t usbcx_dctl;
    usbcx_dctl.u32 = __cvmx_usbd_read_csr32(usb, CVMX_USBCX_DCTL(usb->index));
    usbcx_dctl.s.sgoutnak = 1;
    usbcx_dctl.s.sftdiscon = 1;
    __cvmx_usbd_write_csr32(usb, CVMX_USBCX_DCTL(usb->index), usbcx_dctl.u32);
    return 0;
}