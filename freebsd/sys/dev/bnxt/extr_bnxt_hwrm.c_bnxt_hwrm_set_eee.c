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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_link_speed_mask; } ;
struct bnxt_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  advertised; scalar_t__ tx_lpi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FLAGS_EEE_DISABLE ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FLAGS_EEE_ENABLE ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FLAGS_EEE_TX_LPI ; 
 int /*<<< orphan*/  bnxt_get_fw_auto_link_speeds (int /*<<< orphan*/ ) ; 
 TYPE_1__* eee ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_hwrm_set_eee(struct bnxt_softc *softc, struct hwrm_port_phy_cfg_input *req)
{
	/* struct ethtool_eee *eee = &softc->eee; */
	bool	eee_enabled = false;

	if (eee_enabled) {
#if 0
		uint16_t eee_speeds;
		uint32_t flags = HWRM_PORT_PHY_CFG_INPUT_FLAGS_EEE_ENABLE;

		if (eee->tx_lpi_enabled)
			flags |= HWRM_PORT_PHY_CFG_INPUT_FLAGS_EEE_TX_LPI;

		req->flags |= htole32(flags);
		eee_speeds = bnxt_get_fw_auto_link_speeds(eee->advertised);
		req->eee_link_speed_mask = htole16(eee_speeds);
		req->tx_lpi_timer = htole32(eee->tx_lpi_timer);
#endif
	} else {
		req->flags |=
		    htole32(HWRM_PORT_PHY_CFG_INPUT_FLAGS_EEE_DISABLE);
	}
}