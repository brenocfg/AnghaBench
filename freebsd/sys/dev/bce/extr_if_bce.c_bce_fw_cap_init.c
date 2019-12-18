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
 int /*<<< orphan*/  BCE_DRV_ACK_CAP_MB ; 
 int BCE_DRV_ACK_CAP_SIGNATURE_MAGIC ; 
 int BCE_FW_CAP_BC_KEEP_VLAN ; 
 int /*<<< orphan*/  BCE_FW_CAP_MB ; 
 int BCE_FW_CAP_MFW_KEEP_VLAN ; 
 int BCE_FW_CAP_REMOTE_PHY_CAP ; 
 int BCE_FW_CAP_SIGNATURE_MAGIC ; 
 int BCE_FW_CAP_SIGNATURE_MAGIC_MASK ; 
 int /*<<< orphan*/  BCE_LINK_STATUS ; 
 int BCE_LINK_STATUS_SERDES_LINK ; 
 int BCE_PHY_REMOTE_CAP_FLAG ; 
 int BCE_PHY_REMOTE_PORT_FIBER_FLAG ; 
 int BCE_PHY_SERDES_FLAG ; 
 int bce_shmem_rd (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_shmem_wr (struct bce_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bce_fw_cap_init(struct bce_softc *sc)
{
	u32 ack, cap, link;

	ack = 0;
	cap = bce_shmem_rd(sc, BCE_FW_CAP_MB);
	if ((cap & BCE_FW_CAP_SIGNATURE_MAGIC_MASK) !=
	    BCE_FW_CAP_SIGNATURE_MAGIC)
		return;
	if ((cap & (BCE_FW_CAP_MFW_KEEP_VLAN | BCE_FW_CAP_BC_KEEP_VLAN)) ==
	    (BCE_FW_CAP_MFW_KEEP_VLAN | BCE_FW_CAP_BC_KEEP_VLAN))
		ack |= BCE_DRV_ACK_CAP_SIGNATURE_MAGIC |
		    BCE_FW_CAP_MFW_KEEP_VLAN | BCE_FW_CAP_BC_KEEP_VLAN;
	if ((sc->bce_phy_flags & BCE_PHY_SERDES_FLAG) != 0 &&
	    (cap & BCE_FW_CAP_REMOTE_PHY_CAP) != 0) {
		sc->bce_phy_flags &= ~BCE_PHY_REMOTE_PORT_FIBER_FLAG;
		sc->bce_phy_flags |= BCE_PHY_REMOTE_CAP_FLAG;
		link = bce_shmem_rd(sc, BCE_LINK_STATUS);
		if ((link & BCE_LINK_STATUS_SERDES_LINK) != 0)
			sc->bce_phy_flags |= BCE_PHY_REMOTE_PORT_FIBER_FLAG;
		ack |= BCE_DRV_ACK_CAP_SIGNATURE_MAGIC |
		    BCE_FW_CAP_REMOTE_PHY_CAP;
	}

	if (ack != 0)
		bce_shmem_wr(sc, BCE_DRV_ACK_CAP_MB, ack);
}