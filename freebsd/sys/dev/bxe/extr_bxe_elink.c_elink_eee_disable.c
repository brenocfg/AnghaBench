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
struct elink_vars {int /*<<< orphan*/  eee_status; } ;
struct elink_phy {int dummy; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_EEE_ADV ; 
 scalar_t__ MISC_REG_CPMU_LP_FW_ENABLE_P0 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM_EEE_ADV_STATUS_MASK ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static elink_status_t elink_eee_disable(struct elink_phy *phy,
				struct elink_params *params,
				struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;

	/* Make Certain LPI is disabled */
	REG_WR(sc, MISC_REG_CPMU_LP_FW_ENABLE_P0 + (params->port << 2), 0);

	elink_cl45_write(sc, phy, MDIO_AN_DEVAD, MDIO_AN_REG_EEE_ADV, 0x0);

	vars->eee_status &= ~SHMEM_EEE_ADV_STATUS_MASK;

	return ELINK_STATUS_OK;
}