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
struct elink_phy {int /*<<< orphan*/  def_md_devad; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
#define  ELINK_PHY_INIT 128 
 int /*<<< orphan*/  NIG_REG_XGXS0_CTRL_MD_DEVAD ; 
 int /*<<< orphan*/  NIG_REG_XGXS0_CTRL_MD_ST ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_xgxs_specific_func(struct elink_phy *phy,
				     struct elink_params *params,
				     uint32_t action)
{
	struct bxe_softc *sc = params->sc;
	switch (action) {
	case ELINK_PHY_INIT:
		/* Set correct devad */
		REG_WR(sc, NIG_REG_XGXS0_CTRL_MD_ST + params->port*0x18, 0);
		REG_WR(sc, NIG_REG_XGXS0_CTRL_MD_DEVAD + params->port*0x18,
		       phy->def_md_devad);
		break;
	}
}