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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  MISC_AEU_ENABLE_MCP_PRTY_BITS ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mcp_attn_ctl_regs ; 

__attribute__((used)) static inline void ecore_set_mcp_parity(struct bxe_softc *sc, uint8_t enable)
{
	int i;
	uint32_t reg_val;

	for (i = 0; i < ARRSIZE(mcp_attn_ctl_regs); i++) {
		reg_val = REG_RD(sc, mcp_attn_ctl_regs[i].addr);

		if (enable)
			reg_val |= MISC_AEU_ENABLE_MCP_PRTY_BITS; /* Linux is using mcp_attn_ctl_regs[i].bits */
		else
			reg_val &= ~MISC_AEU_ENABLE_MCP_PRTY_BITS; /* Linux is using mcp_attn_ctl_regs[i].bits */

		REG_WR(sc, mcp_attn_ctl_regs[i].addr, reg_val);
	}
}