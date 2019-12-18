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
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ NIG_REG_LLH0_BRB1_DRV_MASK ; 
 scalar_t__ NIG_REG_LLH0_BRB1_DRV_MASK_MF ; 
 scalar_t__ NIG_REG_LLH0_BRB1_NOT_MCP ; 
 scalar_t__ NIG_REG_LLH1_BRB1_NOT_MCP ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 

void elink_set_rx_filter(struct elink_params *params, uint8_t en)
{
	struct bxe_softc *sc = params->sc;
	uint8_t val = en * 0x1F;

	/* Open / close the gate between the NIG and the BRB */
	if (!CHIP_IS_E1x(sc))
		val |= en * 0x20;
	REG_WR(sc, NIG_REG_LLH0_BRB1_DRV_MASK + params->port*4, val);

	if (!CHIP_IS_E1(sc)) {
		REG_WR(sc, NIG_REG_LLH0_BRB1_DRV_MASK_MF + params->port*4,
		       en*0x3);
	}

	REG_WR(sc, (params->port ? NIG_REG_LLH1_BRB1_NOT_MCP :
		    NIG_REG_LLH0_BRB1_NOT_MCP), en);
}