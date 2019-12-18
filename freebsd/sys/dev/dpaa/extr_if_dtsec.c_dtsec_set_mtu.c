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
struct dtsec_softc {int /*<<< orphan*/  sc_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK_ASSERT (struct dtsec_softc*) ; 
 unsigned int DTSEC_MAX_FRAME_SIZE ; 
 unsigned int DTSEC_MIN_FRAME_SIZE ; 
 int /*<<< orphan*/  DTSEC_REG_MAXFRM ; 
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
dtsec_set_mtu(struct dtsec_softc *sc, unsigned int mtu)
{

	mtu += ETHER_HDR_LEN + ETHER_VLAN_ENCAP_LEN + ETHER_CRC_LEN;

	DTSEC_LOCK_ASSERT(sc);

	if (mtu >= DTSEC_MIN_FRAME_SIZE && mtu <= DTSEC_MAX_FRAME_SIZE) {
		bus_write_4(sc->sc_mem, DTSEC_REG_MAXFRM, mtu);
		return (mtu);
	}

	return (0);
}