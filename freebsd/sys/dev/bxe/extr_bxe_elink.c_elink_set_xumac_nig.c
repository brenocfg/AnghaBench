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
typedef  int /*<<< orphan*/  uint16_t ;
struct elink_params {scalar_t__ port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_P0_MAC_IN_EN ; 
 int /*<<< orphan*/  NIG_REG_P0_MAC_OUT_EN ; 
 int /*<<< orphan*/  NIG_REG_P0_MAC_PAUSE_OUT_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_MAC_IN_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_MAC_OUT_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_MAC_PAUSE_OUT_EN ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_set_xumac_nig(struct elink_params *params,
				uint16_t tx_pause_en,
				uint8_t enable)
{
	struct bxe_softc *sc = params->sc;

	REG_WR(sc, params->port ? NIG_REG_P1_MAC_IN_EN : NIG_REG_P0_MAC_IN_EN,
	       enable);
	REG_WR(sc, params->port ? NIG_REG_P1_MAC_OUT_EN : NIG_REG_P0_MAC_OUT_EN,
	       enable);
	REG_WR(sc, params->port ? NIG_REG_P1_MAC_PAUSE_OUT_EN :
	       NIG_REG_P0_MAC_PAUSE_OUT_EN, tx_pause_en);
}