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
typedef  int uint16_t ;
struct elink_vars {scalar_t__ line_speed; int eee_status; } ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ ELINK_SPEED_100 ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_EEE_ADV ; 
 int SHMEM_EEE_100M_ADV ; 
 int SHMEM_EEE_10G_ADV ; 
 int SHMEM_EEE_1G_ADV ; 
 int SHMEM_EEE_ACTIVE_BIT ; 
 int SHMEM_EEE_LP_ADV_STATUS_MASK ; 
 int SHMEM_EEE_LP_ADV_STATUS_SHIFT ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void elink_eee_an_resolve(struct elink_phy *phy,
				  struct elink_params *params,
				  struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t adv = 0, lp = 0;
	uint32_t lp_adv = 0;
	uint8_t neg = 0;

	elink_cl45_read(sc, phy, MDIO_AN_DEVAD, MDIO_AN_REG_EEE_ADV, &adv);
	elink_cl45_read(sc, phy, MDIO_AN_DEVAD, MDIO_AN_REG_LP_EEE_ADV, &lp);

	if (lp & 0x2) {
		lp_adv |= SHMEM_EEE_100M_ADV;
		if (adv & 0x2) {
			if (vars->line_speed == ELINK_SPEED_100)
				neg = 1;
			ELINK_DEBUG_P0(sc, "EEE negotiated - 100M\n");
		}
	}
	if (lp & 0x14) {
		lp_adv |= SHMEM_EEE_1G_ADV;
		if (adv & 0x14) {
			if (vars->line_speed == ELINK_SPEED_1000)
				neg = 1;
			ELINK_DEBUG_P0(sc, "EEE negotiated - 1G\n");
		}
	}
	if (lp & 0x68) {
		lp_adv |= SHMEM_EEE_10G_ADV;
		if (adv & 0x68) {
			if (vars->line_speed == ELINK_SPEED_10000)
				neg = 1;
			ELINK_DEBUG_P0(sc, "EEE negotiated - 10G\n");
		}
	}

	vars->eee_status &= ~SHMEM_EEE_LP_ADV_STATUS_MASK;
	vars->eee_status |= (lp_adv << SHMEM_EEE_LP_ADV_STATUS_SHIFT);

	if (neg) {
		ELINK_DEBUG_P0(sc, "EEE is active\n");
		vars->eee_status |= SHMEM_EEE_ACTIVE_BIT;
	}
}