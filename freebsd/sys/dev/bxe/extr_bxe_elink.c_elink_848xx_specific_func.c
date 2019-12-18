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
typedef  int uint32_t ;
struct elink_phy {int dummy; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ELINK_NIG_LATCH_BC_ENABLE_MI_INT ; 
#define  ELINK_PHY_INIT 128 
 int /*<<< orphan*/  NIG_REG_LATCH_BC_0 ; 
 int /*<<< orphan*/  elink_848xx_set_led (struct bxe_softc*,struct elink_phy*) ; 
 int /*<<< orphan*/  elink_bits_en (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_is_8483x_8485x (struct elink_phy*) ; 
 int /*<<< orphan*/  elink_save_848xx_spirom_version (struct elink_phy*,struct bxe_softc*,int) ; 

__attribute__((used)) static void elink_848xx_specific_func(struct elink_phy *phy,
				      struct elink_params *params,
				      uint32_t action)
{
	struct bxe_softc *sc = params->sc;
	switch (action) {
	case ELINK_PHY_INIT:
		if (!elink_is_8483x_8485x(phy)) {
			/* Save spirom version */
			elink_save_848xx_spirom_version(phy, sc, params->port);
		}
		/* This phy uses the NIG latch mechanism since link indication
		 * arrives through its LED4 and not via its LASI signal, so we
		 * get steady signal instead of clear on read
		 */
		elink_bits_en(sc, NIG_REG_LATCH_BC_0 + params->port*4,
			      1 << ELINK_NIG_LATCH_BC_ENABLE_MI_INT);

		elink_848xx_set_led(sc, phy);
		break;
	}
}