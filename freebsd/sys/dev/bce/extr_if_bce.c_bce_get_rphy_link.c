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
typedef  int u32 ;
struct bce_softc {int bce_phy_flags; } ;

/* Variables and functions */
 int BCE_NETLINK_ANEG_ENB ; 
 int BCE_NETLINK_ETH_AT_WIRESPEED ; 
 int BCE_NETLINK_FC_PAUSE_ASYM ; 
 int BCE_NETLINK_FC_PAUSE_SYM ; 
 int BCE_NETLINK_PHY_APP_REMOTE ; 
 int BCE_NETLINK_SPEED_1000FULL ; 
 int BCE_NETLINK_SPEED_1000HALF ; 
 int BCE_NETLINK_SPEED_100FULL ; 
 int BCE_NETLINK_SPEED_100HALF ; 
 int BCE_NETLINK_SPEED_10FULL ; 
 int BCE_NETLINK_SPEED_10HALF ; 
 int BCE_NETLINK_SPEED_2500FULL ; 
 int BCE_NETLINK_SPEED_2500HALF ; 
 int BCE_PHY_REMOTE_PORT_FIBER_FLAG ; 
 int /*<<< orphan*/  BCE_RPHY_COPPER_LINK ; 
 int /*<<< orphan*/  BCE_RPHY_SERDES_LINK ; 
 int bce_shmem_rd (struct bce_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
bce_get_rphy_link(struct bce_softc *sc)
{
	u32 advertise, link;
	int fdpx;

	advertise = 0;
	fdpx = 0;
	if ((sc->bce_phy_flags & BCE_PHY_REMOTE_PORT_FIBER_FLAG) != 0)
		link = bce_shmem_rd(sc, BCE_RPHY_SERDES_LINK);
	else
		link = bce_shmem_rd(sc, BCE_RPHY_COPPER_LINK);
	if (link & BCE_NETLINK_ANEG_ENB)
		advertise |= BCE_NETLINK_ANEG_ENB;
	if (link & BCE_NETLINK_SPEED_10HALF)
		advertise |= BCE_NETLINK_SPEED_10HALF;
	if (link & BCE_NETLINK_SPEED_10FULL) {
		advertise |= BCE_NETLINK_SPEED_10FULL;
		fdpx++;
	}
	if (link & BCE_NETLINK_SPEED_100HALF)
		advertise |= BCE_NETLINK_SPEED_100HALF;
	if (link & BCE_NETLINK_SPEED_100FULL) {
		advertise |= BCE_NETLINK_SPEED_100FULL;
		fdpx++;
	}
	if (link & BCE_NETLINK_SPEED_1000HALF)
		advertise |= BCE_NETLINK_SPEED_1000HALF;
	if (link & BCE_NETLINK_SPEED_1000FULL) {
		advertise |= BCE_NETLINK_SPEED_1000FULL;
		fdpx++;
	}
	if (link & BCE_NETLINK_SPEED_2500HALF)
		advertise |= BCE_NETLINK_SPEED_2500HALF;
	if (link & BCE_NETLINK_SPEED_2500FULL) {
		advertise |= BCE_NETLINK_SPEED_2500FULL;
		fdpx++;
	}
	if (fdpx)
		advertise |= BCE_NETLINK_FC_PAUSE_SYM |
		    BCE_NETLINK_FC_PAUSE_ASYM;
	if ((sc->bce_phy_flags & BCE_PHY_REMOTE_PORT_FIBER_FLAG) == 0)
		advertise |= BCE_NETLINK_PHY_APP_REMOTE |
		    BCE_NETLINK_ETH_AT_WIRESPEED;

	return (advertise);
}