#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_udma_m2s_desc_pref_conf {void* pref_thr; void* min_burst_above_thr; void* min_burst_below_thr; void* max_desc_per_packet; int /*<<< orphan*/  sch_mode; void* desc_fifo_depth; } ;
struct al_udma {TYPE_3__* udma_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc_pref_cfg_3; int /*<<< orphan*/  desc_pref_cfg_2; int /*<<< orphan*/  desc_pref_cfg_1; } ;
struct TYPE_5__ {TYPE_1__ m2s_rd; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 void* AL_REG_FIELD_GET (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRR ; 
 int /*<<< orphan*/  STRICT ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_1_FIFO_DEPTH_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_1_FIFO_DEPTH_SHIFT ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_SHIFT ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_SHIFT ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_SHIFT ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_MASK ; 
 int /*<<< orphan*/  UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_SHIFT ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 

int al_udma_m2s_pref_get(struct al_udma *udma,
				struct al_udma_m2s_desc_pref_conf *conf)
{
	uint32_t reg;

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_1);
	conf->desc_fifo_depth =
	    AL_REG_FIELD_GET(reg, UDMA_M2S_RD_DESC_PREF_CFG_1_FIFO_DEPTH_MASK,
			UDMA_M2S_RD_DESC_PREF_CFG_1_FIFO_DEPTH_SHIFT);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_2);
	if (reg & UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_MASK)
		conf->sch_mode = SRR;
	else
		conf->sch_mode = STRICT;
	conf->max_desc_per_packet =
	    AL_REG_FIELD_GET(reg,
			UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_MASK,
			UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_SHIFT);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_3);

	conf->min_burst_below_thr =
	    AL_REG_FIELD_GET(reg,
			UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK,
			UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_SHIFT);

	conf->min_burst_above_thr =
	    AL_REG_FIELD_GET(reg,
			UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK,
			UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_SHIFT);

	conf->pref_thr = AL_REG_FIELD_GET(reg,
				UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_MASK,
				UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_SHIFT);
	return 0;
}