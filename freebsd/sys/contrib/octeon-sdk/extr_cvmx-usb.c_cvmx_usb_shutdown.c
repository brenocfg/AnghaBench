#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int enable; int por; int hclk_rst; scalar_t__ hrst; scalar_t__ prst; } ;
struct TYPE_11__ {int /*<<< orphan*/  u64; TYPE_3__ s; } ;
typedef  TYPE_4__ cvmx_usbnx_clk_ctl_t ;
typedef  int /*<<< orphan*/  cvmx_usb_status_t ;
typedef  int /*<<< orphan*/  cvmx_usb_state_t ;
struct TYPE_8__ {scalar_t__ head; } ;
struct TYPE_12__ {int /*<<< orphan*/  index; TYPE_2__* active_pipes; TYPE_1__ idle_pipes; } ;
typedef  TYPE_5__ cvmx_usb_internal_state_t ;
struct TYPE_9__ {scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ERROR_GROUP_USB ; 
 int /*<<< orphan*/  CVMX_USBNX_CLK_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USB_BUSY ; 
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CVMX_USB_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USB_SUCCESS ; 
 size_t CVMX_USB_TRANSFER_BULK ; 
 size_t CVMX_USB_TRANSFER_CONTROL ; 
 size_t CVMX_USB_TRANSFER_INTERRUPT ; 
 size_t CVMX_USB_TRANSFER_ISOCHRONOUS ; 
 int /*<<< orphan*/  __cvmx_usb_read_csr64 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_usb_write_csr64 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_error_disable_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cvmx_usb_status_t cvmx_usb_shutdown(cvmx_usb_state_t *state)
{
    cvmx_usbnx_clk_ctl_t usbn_clk_ctl;
    cvmx_usb_internal_state_t *usb = (cvmx_usb_internal_state_t*)state;

    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", state);

    /* Make sure all pipes are closed */
    if (usb->idle_pipes.head ||
        usb->active_pipes[CVMX_USB_TRANSFER_ISOCHRONOUS].head ||
        usb->active_pipes[CVMX_USB_TRANSFER_INTERRUPT].head ||
        usb->active_pipes[CVMX_USB_TRANSFER_CONTROL].head ||
        usb->active_pipes[CVMX_USB_TRANSFER_BULK].head)
        CVMX_USB_RETURN(CVMX_USB_BUSY);

#ifdef __CVMX_ERROR_H__
    cvmx_error_disable_group(CVMX_ERROR_GROUP_USB, usb->index);
#endif

    /* Disable the clocks and put them in power on reset */
    usbn_clk_ctl.u64 = __cvmx_usb_read_csr64(usb, CVMX_USBNX_CLK_CTL(usb->index));
    usbn_clk_ctl.s.enable = 1;
    usbn_clk_ctl.s.por = 1;
    usbn_clk_ctl.s.hclk_rst = 1;
    usbn_clk_ctl.s.prst = 0;
    usbn_clk_ctl.s.hrst = 0;
    __cvmx_usb_write_csr64(usb, CVMX_USBNX_CLK_CTL(usb->index),
                           usbn_clk_ctl.u64);
    CVMX_USB_RETURN(CVMX_USB_SUCCESS);
}