#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int pktsts; int bcnt; int chnum; } ;
struct TYPE_10__ {TYPE_1__ s; void* u32; } ;
typedef  TYPE_2__ cvmx_usbcx_grxstsph_t ;
struct TYPE_11__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_3__ cvmx_usb_internal_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SYNCW ; 
 int /*<<< orphan*/  CVMX_USBCX_GRXSTSPH (int /*<<< orphan*/ ) ; 
 scalar_t__ CVMX_USBNX_DMA0_INB_CHN0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  CVMX_USB_RETURN_NOTHING () ; 
 int /*<<< orphan*/  USB_FIFO_ADDRESS (int,int /*<<< orphan*/ ) ; 
 void* __cvmx_usb_read_csr32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __cvmx_usb_read_csr64 (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  __cvmx_usb_write_csr64 (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * cvmx_phys_to_ptr (scalar_t__) ; 

__attribute__((used)) static void __cvmx_usb_poll_rx_fifo(cvmx_usb_internal_state_t *usb)
{
    cvmx_usbcx_grxstsph_t rx_status;
    int channel;
    int bytes;
    uint64_t address;
    uint32_t *ptr;

    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", usb);

    rx_status.u32 = __cvmx_usb_read_csr32(usb, CVMX_USBCX_GRXSTSPH(usb->index));
    /* Only read data if IN data is there */
    if (rx_status.s.pktsts != 2)
        CVMX_USB_RETURN_NOTHING();
    /* Check if no data is available */
    if (!rx_status.s.bcnt)
        CVMX_USB_RETURN_NOTHING();

    channel = rx_status.s.chnum;
    bytes = rx_status.s.bcnt;
    if (!bytes)
        CVMX_USB_RETURN_NOTHING();

    /* Get where the DMA engine would have written this data */
    address = __cvmx_usb_read_csr64(usb, CVMX_USBNX_DMA0_INB_CHN0(usb->index) + channel*8);
    ptr = cvmx_phys_to_ptr(address);
    __cvmx_usb_write_csr64(usb, CVMX_USBNX_DMA0_INB_CHN0(usb->index) + channel*8, address + bytes);

    /* Loop writing the FIFO data for this packet into memory */
    while (bytes > 0)
    {
        *ptr++ = __cvmx_usb_read_csr32(usb, USB_FIFO_ADDRESS(channel, usb->index));
        bytes -= 4;
    }
    CVMX_SYNCW;

    CVMX_USB_RETURN_NOTHING();
}