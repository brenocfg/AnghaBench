#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct octusb_td {TYPE_2__* qh; } ;
struct octusb_softc {TYPE_1__* sc_port; } ;
struct TYPE_4__ {int ep_allocated; size_t root_port_index; int ep_num; scalar_t__ dev_speed; int fixup_handle; int ep_handle; scalar_t__ fixup_actlen; scalar_t__ fixup_pending; scalar_t__ fixup_off; scalar_t__ fixup_len; scalar_t__ fixup_complete; int /*<<< orphan*/  ep_toggle_next; int /*<<< orphan*/  hs_hub_port; int /*<<< orphan*/  hs_hub_addr; int /*<<< orphan*/  ep_mult; int /*<<< orphan*/  ep_interval; int /*<<< orphan*/  ep_type; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  dev_addr; struct octusb_softc* sc; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_DIRECTION_IN ; 
 int /*<<< orphan*/  CVMX_USB_DIRECTION_OUT ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int UE_ADDR ; 
 int UE_DIR_IN ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int cvmx_usb_open_pipe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_set_toggle (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octusb_convert_ep_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octusb_convert_speed (scalar_t__) ; 

__attribute__((used)) static uint8_t
octusb_host_alloc_endpoint(struct octusb_td *td)
{
	struct octusb_softc *sc;
	int ep_handle;

	if (td->qh->fixup_pending)
		return (1);		/* busy */

	if (td->qh->ep_allocated)
		return (0);		/* success */

	/* get softc */
	sc = td->qh->sc;

	ep_handle = cvmx_usb_open_pipe(
	    &sc->sc_port[td->qh->root_port_index].state,
	    0,
	    td->qh->dev_addr,
	    td->qh->ep_num & UE_ADDR,
	    octusb_convert_speed(td->qh->dev_speed),
	    td->qh->max_packet_size,
	    octusb_convert_ep_type(td->qh->ep_type),
	    (td->qh->ep_num & UE_DIR_IN) ? CVMX_USB_DIRECTION_IN :
	    CVMX_USB_DIRECTION_OUT,
	    td->qh->ep_interval,
	    (td->qh->dev_speed == USB_SPEED_HIGH) ? td->qh->ep_mult : 0,
	    td->qh->hs_hub_addr,
	    td->qh->hs_hub_port);

	if (ep_handle < 0) {
		DPRINTFN(1, "cvmx_usb_open_pipe failed: %d\n", ep_handle);
		return (1);		/* busy */
	}

	cvmx_usb_set_toggle(
	    &sc->sc_port[td->qh->root_port_index].state,
	    ep_handle, td->qh->ep_toggle_next);

	td->qh->fixup_handle = -1;
	td->qh->fixup_complete = 0;
	td->qh->fixup_len = 0;
	td->qh->fixup_off = 0;
	td->qh->fixup_pending = 0;
	td->qh->fixup_actlen = 0;

	td->qh->ep_handle = ep_handle;
	td->qh->ep_allocated = 1;

	return (0);			/* success */
}