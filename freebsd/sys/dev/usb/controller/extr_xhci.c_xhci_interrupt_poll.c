#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  uintptr_t uint64_t ;
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  root_pc; } ;
struct xhci_softc {size_t sc_event_idx; int sc_event_ccs; TYPE_1__ sc_hw; } ;
struct xhci_hw_root {TYPE_2__* hwr_events; } ;
struct usb_page_search {uintptr_t physaddr; struct xhci_hw_root* buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwTrb3; int /*<<< orphan*/  dwTrb2; int /*<<< orphan*/  qwTrb0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,size_t,int,long long,long,long) ; 
 int /*<<< orphan*/  XHCI_ERDP_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_ERDP_LO (int /*<<< orphan*/ ) ; 
 uintptr_t XHCI_ERDP_LO_BUSY ; 
 size_t XHCI_MAX_EVENTS ; 
 int XHCI_TRB_3_CYCLE_BIT ; 
 int XHCI_TRB_3_TYPE_GET (int) ; 
#define  XHCI_TRB_EVENT_CMD_COMPLETE 129 
#define  XHCI_TRB_EVENT_TRANSFER 128 
 int /*<<< orphan*/  XWRITE4 (struct xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runt ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int xhci_check_command (struct xhci_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  xhci_check_transfer (struct xhci_softc*,TYPE_2__*) ; 

__attribute__((used)) static int
xhci_interrupt_poll(struct xhci_softc *sc)
{
	struct usb_page_search buf_res;
	struct xhci_hw_root *phwr;
	uint64_t addr;
	uint32_t temp;
	int retval = 0;
	uint16_t i;
	uint8_t event;
	uint8_t j;
	uint8_t k;
	uint8_t t;

	usbd_get_page(&sc->sc_hw.root_pc, 0, &buf_res);

	phwr = buf_res.buffer;

	/* Receive any events */

	usb_pc_cpu_invalidate(&sc->sc_hw.root_pc);

	i = sc->sc_event_idx;
	j = sc->sc_event_ccs;
	t = 2;

	while (1) {

		temp = le32toh(phwr->hwr_events[i].dwTrb3);

		k = (temp & XHCI_TRB_3_CYCLE_BIT) ? 1 : 0;

		if (j != k)
			break;

		event = XHCI_TRB_3_TYPE_GET(temp);

		DPRINTFN(10, "event[%u] = %u (0x%016llx 0x%08lx 0x%08lx)\n",
		    i, event, (long long)le64toh(phwr->hwr_events[i].qwTrb0),
		    (long)le32toh(phwr->hwr_events[i].dwTrb2),
		    (long)le32toh(phwr->hwr_events[i].dwTrb3));

		switch (event) {
		case XHCI_TRB_EVENT_TRANSFER:
			xhci_check_transfer(sc, &phwr->hwr_events[i]);
			break;
		case XHCI_TRB_EVENT_CMD_COMPLETE:
			retval |= xhci_check_command(sc, &phwr->hwr_events[i]);
			break;
		default:
			DPRINTF("Unhandled event = %u\n", event);
			break;
		}

		i++;

		if (i == XHCI_MAX_EVENTS) {
			i = 0;
			j ^= 1;

			/* check for timeout */
			if (!--t)
				break;
		}
	}

	sc->sc_event_idx = i;
	sc->sc_event_ccs = j;

	/*
	 * NOTE: The Event Ring Dequeue Pointer Register is 64-bit
	 * latched. That means to activate the register we need to
	 * write both the low and high double word of the 64-bit
	 * register.
	 */

	addr = buf_res.physaddr;
	addr += (uintptr_t)&((struct xhci_hw_root *)0)->hwr_events[i];

	/* try to clear busy bit */
	addr |= XHCI_ERDP_LO_BUSY;

	XWRITE4(sc, runt, XHCI_ERDP_LO(0), (uint32_t)addr);
	XWRITE4(sc, runt, XHCI_ERDP_HI(0), (uint32_t)(addr >> 32));

	return (retval);
}