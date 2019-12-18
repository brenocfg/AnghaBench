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
 int /*<<< orphan*/  AL_UDMA_PRINT_REG_FIELD (struct al_udma*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR ; 
 int /*<<< orphan*/  al_dbg (char*) ; 
 int /*<<< orphan*/  data_cfg ; 
 int /*<<< orphan*/  desc_pref_cfg_1 ; 
 int /*<<< orphan*/  desc_pref_cfg_2 ; 
 int /*<<< orphan*/  desc_pref_cfg_3 ; 
 int /*<<< orphan*/  m2s ; 
 int /*<<< orphan*/  m2s_rd ; 
 int /*<<< orphan*/  min_burst_above_thr ; 
 int /*<<< orphan*/  min_burst_below_thr ; 
 int /*<<< orphan*/  pref_thr ; 

__attribute__((used)) static void al_udma_regs_m2s_rd_print(struct al_udma *udma)
{
	al_dbg("M2S read regs:\n");
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_rd, desc_pref_cfg_1);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_rd, desc_pref_cfg_2);

	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_rd, desc_pref_cfg_3);
	AL_UDMA_PRINT_REG_FIELD(udma, "  ", "\n", "%d", m2s, m2s_rd,
			desc_pref_cfg_3,
			min_burst_below_thr,
			UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR);
	AL_UDMA_PRINT_REG_FIELD(udma, "  ", "\n", "%d", m2s, m2s_rd,
			desc_pref_cfg_3,
			min_burst_above_thr,
			UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR);
	AL_UDMA_PRINT_REG_FIELD(udma, "  ", "\n", "%d", m2s, m2s_rd,
			desc_pref_cfg_3,
			pref_thr,
			UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR);

	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_rd, data_cfg);
}