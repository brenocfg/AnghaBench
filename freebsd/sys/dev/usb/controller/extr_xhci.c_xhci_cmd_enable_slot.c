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
typedef  scalar_t__ usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct xhci_trb {int /*<<< orphan*/  dwTrb3; scalar_t__ dwTrb2; scalar_t__ qwTrb0; } ;
struct xhci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  XHCI_TRB_3_SLOT_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_TRB_3_TYPE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_TRB_TYPE_ENABLE_SLOT ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_do_command (struct xhci_softc*,struct xhci_trb*,int) ; 

__attribute__((used)) static usb_error_t
xhci_cmd_enable_slot(struct xhci_softc *sc, uint8_t *pslot)
{
	struct xhci_trb trb;
	uint32_t temp;
	usb_error_t err;

	DPRINTF("\n");

	trb.qwTrb0 = 0;
	trb.dwTrb2 = 0;
	trb.dwTrb3 = htole32(XHCI_TRB_3_TYPE_SET(XHCI_TRB_TYPE_ENABLE_SLOT));

	err = xhci_do_command(sc, &trb, 100 /* ms */);
	if (err)
		goto done;

	temp = le32toh(trb.dwTrb3);

	*pslot = XHCI_TRB_3_SLOT_GET(temp); 

done:
	return (err);
}