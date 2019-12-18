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
struct aue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aue_read_mac (struct aue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aue_reset (struct aue_softc*) ; 
 struct aue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
aue_attach_post(struct usb_ether *ue)
{
	struct aue_softc *sc = uether_getsc(ue);

	/* reset the adapter */
	aue_reset(sc);

	/* get station address from the EEPROM */
	aue_read_mac(sc, ue->ue_eaddr);
}