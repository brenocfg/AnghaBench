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
typedef  int uint16_t ;
struct elink_phy {scalar_t__ req_line_speed; } ;
struct elink_params {int /*<<< orphan*/  port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int ELINK_STATUS_OK ; 
 int /*<<< orphan*/  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS ; 
 int MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS_PD_LINK ; 
 int /*<<< orphan*/  MDIO_REG_BANK_10G_PARALLEL_DETECT ; 
 int /*<<< orphan*/  MDIO_REG_BANK_SERDES_DIGITAL ; 
 int /*<<< orphan*/  MDIO_SERDES_DIGITAL_A_1000X_STATUS2 ; 
 int MDIO_SERDES_DIGITAL_A_1000X_STATUS2_AN_DISABLED ; 

__attribute__((used)) static elink_status_t elink_direct_parallel_detect_used(struct elink_phy *phy,
					     struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	uint16_t pd_10g, status2_1000x;
	if (phy->req_line_speed != ELINK_SPEED_AUTO_NEG)
		return ELINK_STATUS_OK;
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_STATUS2,
			  &status2_1000x);
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_STATUS2,
			  &status2_1000x);
	if (status2_1000x & MDIO_SERDES_DIGITAL_A_1000X_STATUS2_AN_DISABLED) {
		ELINK_DEBUG_P1(sc, "1G parallel detect link on port %d\n",
			 params->port);
		return 1;
	}

	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_10G_PARALLEL_DETECT,
			  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS,
			  &pd_10g);

	if (pd_10g & MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS_PD_LINK) {
		ELINK_DEBUG_P1(sc, "10G parallel detect link on port %d\n",
			 params->port);
		return 1;
	}
	return ELINK_STATUS_OK;
}