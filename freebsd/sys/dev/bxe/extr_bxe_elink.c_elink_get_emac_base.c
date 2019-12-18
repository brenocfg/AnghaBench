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

/* Variables and functions */
 int GRCBASE_EMAC0 ; 
 int GRCBASE_EMAC1 ; 
 int /*<<< orphan*/  NIG_REG_PORT_SWAP ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
#define  SHARED_HW_CFG_MDC_MDIO_ACCESS1_BOTH 132 
#define  SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC0 131 
#define  SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC1 130 
#define  SHARED_HW_CFG_MDC_MDIO_ACCESS1_PHY_TYPE 129 
#define  SHARED_HW_CFG_MDC_MDIO_ACCESS1_SWAPPED 128 

__attribute__((used)) static uint32_t elink_get_emac_base(struct bxe_softc *sc,
			       uint32_t mdc_mdio_access, uint8_t port)
{
	uint32_t emac_base = 0;
	switch (mdc_mdio_access) {
	case SHARED_HW_CFG_MDC_MDIO_ACCESS1_PHY_TYPE:
		break;
	case SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC0:
		if (REG_RD(sc, NIG_REG_PORT_SWAP))
			emac_base = GRCBASE_EMAC1;
		else
			emac_base = GRCBASE_EMAC0;
		break;
	case SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC1:
		if (REG_RD(sc, NIG_REG_PORT_SWAP))
			emac_base = GRCBASE_EMAC0;
		else
			emac_base = GRCBASE_EMAC1;
		break;
	case SHARED_HW_CFG_MDC_MDIO_ACCESS1_BOTH:
		emac_base = (port) ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
		break;
	case SHARED_HW_CFG_MDC_MDIO_ACCESS1_SWAPPED:
		emac_base = (port) ? GRCBASE_EMAC0 : GRCBASE_EMAC1;
		break;
	default:
		break;
	}
	return emac_base;

}