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
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_sfp_e1e2_set_transmitter (struct elink_params*,struct elink_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_sfp_e3_set_transmitter (struct elink_params*,struct elink_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_sfp_set_transmitter(struct elink_params *params,
				      struct elink_phy *phy,
				      uint8_t tx_en)
{
	struct bxe_softc *sc = params->sc;
	ELINK_DEBUG_P1(sc, "Setting SFP+ transmitter to %d\n", tx_en);
	if (CHIP_IS_E3(sc))
		elink_sfp_e3_set_transmitter(params, phy, tx_en);
	else
		elink_sfp_e1e2_set_transmitter(params, phy, tx_en);
}