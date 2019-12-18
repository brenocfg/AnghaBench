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
struct usb_ether {int /*<<< orphan*/  ue_eaddr; } ;
struct mos_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOS_DPRINTFN (char*,...) ; 
 int /*<<< orphan*/  ether_sprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_chip_init (struct mos_softc*) ; 
 int mos_readmac (struct mos_softc*,int /*<<< orphan*/ ) ; 
 struct mos_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
mos_attach_post(struct usb_ether *ue)
{
	struct mos_softc *sc = uether_getsc(ue);
        int err;

	/* Read MAC address, inform the world. */
	err = mos_readmac(sc, ue->ue_eaddr);

	if (err)
	  MOS_DPRINTFN("couldn't get MAC address");

	MOS_DPRINTFN("address: %s", ether_sprintf(ue->ue_eaddr));

	mos_chip_init(sc);
}