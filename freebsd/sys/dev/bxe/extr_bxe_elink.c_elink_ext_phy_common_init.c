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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;
typedef  scalar_t__ elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_LOG_ID_PHY_UNINITIALIZED ; 
 scalar_t__ ELINK_STATUS_ERROR ; 
 scalar_t__ ELINK_STATUS_OK ; 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073 136 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833 135 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834 134 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858 133 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 132 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726 131 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 130 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727_NOC 129 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE 128 
 scalar_t__ elink_8073_common_init_phy (struct bxe_softc*,int*,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ elink_84833_common_init_phy (struct bxe_softc*,int*,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ elink_8726_common_init_phy (struct bxe_softc*,int*,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ elink_8727_common_init_phy (struct bxe_softc*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cb_event_log (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static elink_status_t elink_ext_phy_common_init(struct bxe_softc *sc, uint32_t shmem_base_path[],
				     uint32_t shmem2_base_path[], uint8_t phy_index,
				     uint32_t ext_phy_type, uint32_t chip_id)
{
	elink_status_t rc = ELINK_STATUS_OK;

	switch (ext_phy_type) {
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073:
		rc = elink_8073_common_init_phy(sc, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727_NOC:
		rc = elink_8727_common_init_phy(sc, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		break;

	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		/* GPIO1 affects both ports, so there's need to pull
		 * it for single port alone
		 */
		rc = elink_8726_common_init_phy(sc, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858:
		/* GPIO3's are linked, and so both need to be toggled
		 * to obtain required 2us pulse.
		 */
		rc = elink_84833_common_init_phy(sc, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE:
		rc = ELINK_STATUS_ERROR;
		break;
	default:
		ELINK_DEBUG_P1(sc,
			   "ext_phy 0x%x common init not required\n",
			   ext_phy_type);
		break;
	}

	if (rc != ELINK_STATUS_OK)
		elink_cb_event_log(sc, ELINK_LOG_ID_PHY_UNINITIALIZED, 0); // "Warning: PHY was not initialized,"
				     // " Port %d\n",

	return rc;
}