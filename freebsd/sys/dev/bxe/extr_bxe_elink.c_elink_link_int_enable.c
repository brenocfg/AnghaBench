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
typedef  int uint32_t ;
struct elink_params {int port; scalar_t__ switch_cfg; TYPE_1__* phy; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,int,int,int) ; 
 size_t ELINK_INT_PHY ; 
 int ELINK_NIG_MASK_MI_INT ; 
 int ELINK_NIG_MASK_SERDES0_LINK_STATUS ; 
 int ELINK_NIG_MASK_XGXS0_LINK10G ; 
 int ELINK_NIG_MASK_XGXS0_LINK_STATUS ; 
 int /*<<< orphan*/  ELINK_SINGLE_MEDIA_DIRECT (struct elink_params*) ; 
 scalar_t__ ELINK_SWITCH_CFG_10G ; 
 scalar_t__ NIG_REG_EMAC0_STATUS_MISC_MI_INT ; 
 scalar_t__ NIG_REG_MASK_INTERRUPT_PORT0 ; 
 scalar_t__ NIG_REG_SERDES0_STATUS_LINK_STATUS ; 
 scalar_t__ NIG_REG_STATUS_INTERRUPT_PORT0 ; 
 scalar_t__ NIG_REG_XGXS0_STATUS_LINK10G ; 
 scalar_t__ NIG_REG_XGXS0_STATUS_LINK_STATUS ; 
 scalar_t__ PORT_HW_CFG_SERDES_EXT_PHY_TYPE_NOT_CONN ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  elink_bits_en (struct bxe_softc*,scalar_t__,int) ; 

__attribute__((used)) static void elink_link_int_enable(struct elink_params *params)
{
	uint8_t port = params->port;
	uint32_t mask;
	struct bxe_softc *sc = params->sc;

	/* Setting the status to report on link up for either XGXS or SerDes */
	if (CHIP_IS_E3(sc)) {
		mask = ELINK_NIG_MASK_XGXS0_LINK_STATUS;
		if (!(ELINK_SINGLE_MEDIA_DIRECT(params)))
			mask |= ELINK_NIG_MASK_MI_INT;
	} else if (params->switch_cfg == ELINK_SWITCH_CFG_10G) {
		mask = (ELINK_NIG_MASK_XGXS0_LINK10G |
			ELINK_NIG_MASK_XGXS0_LINK_STATUS);
		ELINK_DEBUG_P0(sc, "enabled XGXS interrupt\n");
		if (!(ELINK_SINGLE_MEDIA_DIRECT(params)) &&
			params->phy[ELINK_INT_PHY].type !=
				PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE) {
			mask |= ELINK_NIG_MASK_MI_INT;
			ELINK_DEBUG_P0(sc, "enabled external phy int\n");
		}

	} else { /* SerDes */
		mask = ELINK_NIG_MASK_SERDES0_LINK_STATUS;
		ELINK_DEBUG_P0(sc, "enabled SerDes interrupt\n");
		if (!(ELINK_SINGLE_MEDIA_DIRECT(params)) &&
			params->phy[ELINK_INT_PHY].type !=
				PORT_HW_CFG_SERDES_EXT_PHY_TYPE_NOT_CONN) {
			mask |= ELINK_NIG_MASK_MI_INT;
			ELINK_DEBUG_P0(sc, "enabled external phy int\n");
		}
	}
	elink_bits_en(sc,
		      NIG_REG_MASK_INTERRUPT_PORT0 + port*4,
		      mask);

	ELINK_DEBUG_P3(sc, "port %x, is_xgxs %x, int_status 0x%x\n", port,
		 (params->switch_cfg == ELINK_SWITCH_CFG_10G),
		 REG_RD(sc, NIG_REG_STATUS_INTERRUPT_PORT0 + port*4));
	ELINK_DEBUG_P3(sc, " int_mask 0x%x, MI_INT %x, SERDES_LINK %x\n",
		 REG_RD(sc, NIG_REG_MASK_INTERRUPT_PORT0 + port*4),
		 REG_RD(sc, NIG_REG_EMAC0_STATUS_MISC_MI_INT + port*0x18),
		 REG_RD(sc, NIG_REG_SERDES0_STATUS_LINK_STATUS+port*0x3c));
	ELINK_DEBUG_P2(sc, " 10G %x, XGXS_LINK %x\n",
	   REG_RD(sc, NIG_REG_XGXS0_STATUS_LINK10G + port*0x68),
	   REG_RD(sc, NIG_REG_XGXS0_STATUS_LINK_STATUS + port*0x68));
}