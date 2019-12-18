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
struct elink_phy {int dummy; } ;
struct elink_params {int feature_config_flags; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int ELINK_FEATURE_CONFIG_BC_SUPPORTS_SFP_TX_DISABLED ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_TX_DISABLE ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void elink_set_disable_pmd_transmit(struct elink_params *params,
					   struct elink_phy *phy,
					   uint8_t pmd_dis)
{
	struct bxe_softc *sc = params->sc;
	/* Disable transmitter only for bootcodes which can enable it afterwards
	 * (for D3 link)
	 */
	if (pmd_dis) {
		if (params->feature_config_flags &
		     ELINK_FEATURE_CONFIG_BC_SUPPORTS_SFP_TX_DISABLED) {
			ELINK_DEBUG_P0(sc, "Disabling PMD transmitter\n");
		} else {
			ELINK_DEBUG_P0(sc, "NOT disabling PMD transmitter\n");
			return;
		}
	} else
		ELINK_DEBUG_P0(sc, "Enabling PMD transmitter\n");
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_TX_DISABLE, pmd_dis);
}