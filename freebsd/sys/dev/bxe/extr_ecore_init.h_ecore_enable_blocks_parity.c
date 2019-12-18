#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;
struct TYPE_3__ {int en_mask; int /*<<< orphan*/  mask_addr; } ;

/* Variables and functions */
 int ARRSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* ecore_blocks_parity_data ; 
 int ecore_parity_reg_mask (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  ecore_set_mcp_parity (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ecore_enable_blocks_parity(struct bxe_softc *sc)
{
	int i;

	for (i = 0; i < ARRSIZE(ecore_blocks_parity_data); i++) {
		uint32_t reg_mask = ecore_parity_reg_mask(sc, i);

		if (reg_mask)
			REG_WR(sc, ecore_blocks_parity_data[i].mask_addr,
				ecore_blocks_parity_data[i].en_mask & reg_mask);
	}

	/* Enable MCP parity attentions */
	ecore_set_mcp_parity(sc, TRUE);
}