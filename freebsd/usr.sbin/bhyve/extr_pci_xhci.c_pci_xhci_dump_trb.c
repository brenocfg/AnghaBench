#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
struct xhci_trb {int /*<<< orphan*/  dwTrb3; int /*<<< orphan*/  dwTrb2; int /*<<< orphan*/  qwTrb0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 size_t XHCI_TRB_3_TYPE_GET (int /*<<< orphan*/ ) ; 
 size_t XHCI_TRB_TYPE_NOOP_CMD ; 

__attribute__((used)) static void
pci_xhci_dump_trb(struct xhci_trb *trb)
{
	static const char *trbtypes[] = {
		"RESERVED",
		"NORMAL",
		"SETUP_STAGE",
		"DATA_STAGE",
		"STATUS_STAGE",
		"ISOCH",
		"LINK",
		"EVENT_DATA",
		"NOOP",
		"ENABLE_SLOT",
		"DISABLE_SLOT",
		"ADDRESS_DEVICE",
		"CONFIGURE_EP",
		"EVALUATE_CTX",
		"RESET_EP",
		"STOP_EP",
		"SET_TR_DEQUEUE",
		"RESET_DEVICE",
		"FORCE_EVENT",
		"NEGOTIATE_BW",
		"SET_LATENCY_TOL",
		"GET_PORT_BW",
		"FORCE_HEADER",
		"NOOP_CMD"
	};
	uint32_t type;

	type = XHCI_TRB_3_TYPE_GET(trb->dwTrb3);
	DPRINTF(("pci_xhci: trb[@%p] type x%02x %s 0:x%016lx 2:x%08x 3:x%08x\r\n",
	         trb, type,
	         type <= XHCI_TRB_TYPE_NOOP_CMD ? trbtypes[type] : "INVALID",
	         trb->qwTrb0, trb->dwTrb2, trb->dwTrb3));
}