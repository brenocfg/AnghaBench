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
struct al_udma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_UDMA_PRINT_REG (struct al_udma*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_UDMA_PRINT_REG_BIT (struct al_udma*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_UDMA_PRINT_REG_FIELD (struct al_udma*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDMA_M2S_COMP_CFG_1C_COMP_FIFO_DEPTH ; 
 int /*<<< orphan*/  UDMA_M2S_COMP_CFG_1C_FORCE_RR ; 
 int /*<<< orphan*/  UDMA_M2S_COMP_CFG_1C_Q_FREE_MIN ; 
 int /*<<< orphan*/  UDMA_M2S_COMP_CFG_1C_Q_PROMOTION ; 
 int /*<<< orphan*/  UDMA_M2S_COMP_CFG_1C_UNACK_FIFO_DEPTH ; 
 int /*<<< orphan*/  al_dbg (char*) ; 
 int /*<<< orphan*/  cfg_1c ; 
 int /*<<< orphan*/  cfg_application_ack ; 
 int /*<<< orphan*/  cfg_coal ; 
 int /*<<< orphan*/  comp_fifo_depth ; 
 int /*<<< orphan*/  force_rr ; 
 int /*<<< orphan*/  m2s ; 
 int /*<<< orphan*/  m2s_comp ; 
 int /*<<< orphan*/  q_free_min ; 
 int /*<<< orphan*/  q_promotion ; 
 int /*<<< orphan*/  unack_fifo_depth ; 

__attribute__((used)) static void al_udma_regs_m2s_comp_print(struct al_udma *udma)
{
	al_dbg("M2S completion regs:\n");

	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_comp, cfg_1c);

	AL_UDMA_PRINT_REG_FIELD(udma, "  ", "\n", "%d", m2s, m2s_comp, cfg_1c,
			comp_fifo_depth,
			UDMA_M2S_COMP_CFG_1C_COMP_FIFO_DEPTH);
	AL_UDMA_PRINT_REG_FIELD(udma, "  ", "\n", "%d", m2s, m2s_comp, cfg_1c,
			unack_fifo_depth,
			UDMA_M2S_COMP_CFG_1C_UNACK_FIFO_DEPTH);
	AL_UDMA_PRINT_REG_BIT(udma, "  ", "\n", m2s, m2s_comp, cfg_1c,
			q_promotion,
			UDMA_M2S_COMP_CFG_1C_Q_PROMOTION);
	AL_UDMA_PRINT_REG_BIT(udma, "  ", "\n", m2s, m2s_comp, cfg_1c,
			force_rr,
			UDMA_M2S_COMP_CFG_1C_FORCE_RR);
	AL_UDMA_PRINT_REG_FIELD(udma, "  ", "\n", "%d", m2s, m2s_comp, cfg_1c,
			q_free_min,
			UDMA_M2S_COMP_CFG_1C_Q_FREE_MIN);

	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_comp, cfg_coal);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_comp, cfg_application_ack);
}