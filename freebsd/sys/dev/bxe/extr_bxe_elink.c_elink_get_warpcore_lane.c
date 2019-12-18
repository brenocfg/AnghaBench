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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct elink_phy {int dummy; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_REG_FOUR_PORT_PATH_SWAP ; 
 int /*<<< orphan*/  MISC_REG_FOUR_PORT_PATH_SWAP_OVWR ; 
 int /*<<< orphan*/  MISC_REG_FOUR_PORT_PORT_SWAP ; 
 int /*<<< orphan*/  MISC_REG_FOUR_PORT_PORT_SWAP_OVWR ; 
 int /*<<< orphan*/  MISC_REG_TWO_PORT_PATH_SWAP ; 
 int /*<<< orphan*/  MISC_REG_TWO_PORT_PATH_SWAP_OVWR ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int SC_PATH (struct bxe_softc*) ; 
 scalar_t__ elink_is_4_port_mode (struct bxe_softc*) ; 

__attribute__((used)) static uint8_t elink_get_warpcore_lane(struct elink_phy *phy,
				  struct elink_params *params)
{
	uint8_t lane = 0;
	struct bxe_softc *sc = params->sc;
	uint32_t path_swap, path_swap_ovr;
	uint8_t path, port;

	path = SC_PATH(sc);
	port = params->port;

	if (elink_is_4_port_mode(sc)) {
		uint32_t port_swap, port_swap_ovr;

		/* Figure out path swap value */
		path_swap_ovr = REG_RD(sc, MISC_REG_FOUR_PORT_PATH_SWAP_OVWR);
		if (path_swap_ovr & 0x1)
			path_swap = (path_swap_ovr & 0x2);
		else
			path_swap = REG_RD(sc, MISC_REG_FOUR_PORT_PATH_SWAP);

		if (path_swap)
			path = path ^ 1;

		/* Figure out port swap value */
		port_swap_ovr = REG_RD(sc, MISC_REG_FOUR_PORT_PORT_SWAP_OVWR);
		if (port_swap_ovr & 0x1)
			port_swap = (port_swap_ovr & 0x2);
		else
			port_swap = REG_RD(sc, MISC_REG_FOUR_PORT_PORT_SWAP);

		if (port_swap)
			port = port ^ 1;

		lane = (port<<1) + path;
	} else { /* Two port mode - no port swap */

		/* Figure out path swap value */
		path_swap_ovr =
			REG_RD(sc, MISC_REG_TWO_PORT_PATH_SWAP_OVWR);
		if (path_swap_ovr & 0x1) {
			path_swap = (path_swap_ovr & 0x2);
		} else {
			path_swap =
				REG_RD(sc, MISC_REG_TWO_PORT_PATH_SWAP);
		}
		if (path_swap)
			path = path ^ 1;

		lane = path << 1 ;
	}
	return lane;
}