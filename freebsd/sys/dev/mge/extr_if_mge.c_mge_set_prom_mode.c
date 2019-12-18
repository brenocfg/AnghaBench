#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct mge_softc {TYPE_1__* ifp; } ;
struct TYPE_2__ {int if_flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MGE_DA_FILTER_OTH_MCAST (scalar_t__) ; 
 int /*<<< orphan*/  MGE_DA_FILTER_SPEC_MCAST (scalar_t__) ; 
 int /*<<< orphan*/  MGE_DA_FILTER_UCAST (scalar_t__) ; 
 scalar_t__ MGE_MCAST_REG_NUMBER ; 
 int /*<<< orphan*/  MGE_PORT_CONFIG ; 
 scalar_t__ MGE_READ (struct mge_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ MGE_UCAST_REG_NUMBER ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PORT_CONFIG_UPM ; 
 int /*<<< orphan*/  mge_set_mac_address (struct mge_softc*) ; 

__attribute__((used)) static void
mge_set_prom_mode(struct mge_softc *sc, uint8_t queue)
{
	uint32_t port_config;
	uint32_t reg_val, i;

	/* Enable or disable promiscuous mode as needed */
	if (sc->ifp->if_flags & IFF_PROMISC) {
		port_config = MGE_READ(sc, MGE_PORT_CONFIG);
		port_config |= PORT_CONFIG_UPM;
		MGE_WRITE(sc, MGE_PORT_CONFIG, port_config);

		reg_val = ((1 | (queue << 1)) | (1 | (queue << 1)) << 8 |
		   (1 | (queue << 1)) << 16 | (1 | (queue << 1)) << 24);

		for (i = 0; i < MGE_MCAST_REG_NUMBER; i++) {
			MGE_WRITE(sc, MGE_DA_FILTER_SPEC_MCAST(i), reg_val);
			MGE_WRITE(sc, MGE_DA_FILTER_OTH_MCAST(i), reg_val);
		}

		for (i = 0; i < MGE_UCAST_REG_NUMBER; i++)
			MGE_WRITE(sc, MGE_DA_FILTER_UCAST(i), reg_val);

	} else {
		port_config = MGE_READ(sc, MGE_PORT_CONFIG);
		port_config &= ~PORT_CONFIG_UPM;
		MGE_WRITE(sc, MGE_PORT_CONFIG, port_config);

		for (i = 0; i < MGE_MCAST_REG_NUMBER; i++) {
			MGE_WRITE(sc, MGE_DA_FILTER_SPEC_MCAST(i), 0);
			MGE_WRITE(sc, MGE_DA_FILTER_OTH_MCAST(i), 0);
		}

		mge_set_mac_address(sc);
	}
}