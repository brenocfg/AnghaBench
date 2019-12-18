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
typedef  int uint16_t ;
struct TYPE_5__ {scalar_t__* sc_intr_stat; } ;
typedef  TYPE_2__ uhci_softc_t ;
struct usb_xfer {int interval; int qh_pos; TYPE_1__* xroot; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int) ; 
 TYPE_2__* UHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int UHCI_IFRAMELIST_COUNT ; 

__attribute__((used)) static void
uhci_device_intr_open(struct usb_xfer *xfer)
{
	uhci_softc_t *sc = UHCI_BUS2SC(xfer->xroot->bus);
	uint16_t best;
	uint16_t bit;
	uint16_t x;

	best = 0;
	bit = UHCI_IFRAMELIST_COUNT / 2;
	while (bit) {
		if (xfer->interval >= bit) {
			x = bit;
			best = bit;
			while (x & bit) {
				if (sc->sc_intr_stat[x] <
				    sc->sc_intr_stat[best]) {
					best = x;
				}
				x++;
			}
			break;
		}
		bit >>= 1;
	}

	sc->sc_intr_stat[best]++;
	xfer->qh_pos = best;

	DPRINTFN(3, "best=%d interval=%d\n",
	    best, xfer->interval);
}