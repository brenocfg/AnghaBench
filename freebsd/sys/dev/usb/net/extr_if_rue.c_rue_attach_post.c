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
struct rue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  RUE_EEPROM_IDR0 ; 
 int /*<<< orphan*/  rue_read_mem (struct rue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rue_reset (struct rue_softc*) ; 
 struct rue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
rue_attach_post(struct usb_ether *ue)
{
	struct rue_softc *sc = uether_getsc(ue);

	/* reset the adapter */
	rue_reset(sc);

	/* get station address from the EEPROM */
	rue_read_mem(sc, RUE_EEPROM_IDR0, ue->ue_eaddr, ETHER_ADDR_LEN);
}