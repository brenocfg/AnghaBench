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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct elink_phy {int /*<<< orphan*/  type; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 scalar_t__ ELINK_INT_PHY ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN ; 
 int /*<<< orphan*/  elink_populate_ext_phy (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct elink_phy*) ; 
 int /*<<< orphan*/  elink_populate_int_phy (struct bxe_softc*,int /*<<< orphan*/ ,scalar_t__,struct elink_phy*) ; 

__attribute__((used)) static elink_status_t elink_populate_phy(struct bxe_softc *sc, uint8_t phy_index, uint32_t shmem_base,
			      uint32_t shmem2_base, uint8_t port, struct elink_phy *phy)
{
	elink_status_t status = ELINK_STATUS_OK;
	phy->type = PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN;
	if (phy_index == ELINK_INT_PHY)
		return elink_populate_int_phy(sc, shmem_base, port, phy);
	status = elink_populate_ext_phy(sc, phy_index, shmem_base, shmem2_base,
					port, phy);
	return status;
}