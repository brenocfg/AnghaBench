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
typedef  char uint32_t ;
struct mge_softc {int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 scalar_t__ IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_GLOBAL_LOCK_ASSERT (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_MAC_ADDR_H ; 
 int /*<<< orphan*/  MGE_MAC_ADDR_L ; 
 int /*<<< orphan*/  MGE_RX_DEFAULT_QUEUE ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  mge_set_ucast_address (struct mge_softc*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mge_set_mac_address(struct mge_softc *sc)
{
	char *if_mac;
	uint32_t mac_l, mac_h;

	MGE_GLOBAL_LOCK_ASSERT(sc);

	if_mac = (char *)IF_LLADDR(sc->ifp);

	mac_l = (if_mac[4] << 8) | (if_mac[5]);
	mac_h = (if_mac[0] << 24)| (if_mac[1] << 16) |
	    (if_mac[2] << 8) | (if_mac[3] << 0);

	MGE_WRITE(sc, MGE_MAC_ADDR_L, mac_l);
	MGE_WRITE(sc, MGE_MAC_ADDR_H, mac_h);

	mge_set_ucast_address(sc, if_mac[5], MGE_RX_DEFAULT_QUEUE);
}