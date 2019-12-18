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
struct udav_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  UDAV_PAR ; 
 int /*<<< orphan*/  udav_csr_read (struct udav_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udav_reset (struct udav_softc*) ; 
 struct udav_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
udav_attach_post(struct usb_ether *ue)
{
	struct udav_softc *sc = uether_getsc(ue);

	/* reset the adapter */
	udav_reset(sc);

	/* Get Ethernet Address */
	udav_csr_read(sc, UDAV_PAR, ue->ue_eaddr, ETHER_ADDR_LEN);
}