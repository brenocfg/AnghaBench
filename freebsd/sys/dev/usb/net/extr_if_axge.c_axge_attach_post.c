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
struct axge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_ACCESS_MAC ; 
 int /*<<< orphan*/  AXGE_NIDR ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  axge_chip_init (struct axge_softc*) ; 
 int /*<<< orphan*/  axge_read_mem (struct axge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axge_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
axge_attach_post(struct usb_ether *ue)
{
	struct axge_softc *sc;

	sc = uether_getsc(ue);

	/* Initialize controller and get station address. */
	axge_chip_init(sc);
	axge_read_mem(sc, AXGE_ACCESS_MAC, ETHER_ADDR_LEN, AXGE_NIDR,
	    ue->ue_eaddr, ETHER_ADDR_LEN);
}