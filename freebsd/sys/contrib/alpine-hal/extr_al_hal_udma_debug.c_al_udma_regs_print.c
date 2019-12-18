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
typedef  scalar_t__ uint32_t ;
struct al_udma {scalar_t__ type; } ;

/* Variables and functions */
 unsigned int AL_UDMA_DEBUG_AXI ; 
 unsigned int AL_UDMA_DEBUG_COMP ; 
 unsigned int AL_UDMA_DEBUG_DWRR ; 
 unsigned int AL_UDMA_DEBUG_FEATURE ; 
 unsigned int AL_UDMA_DEBUG_GENERAL ; 
 unsigned int AL_UDMA_DEBUG_QUEUE (scalar_t__) ; 
 unsigned int AL_UDMA_DEBUG_RATE_LIMITER ; 
 unsigned int AL_UDMA_DEBUG_READ ; 
 unsigned int AL_UDMA_DEBUG_STAT ; 
 unsigned int AL_UDMA_DEBUG_STREAM_RATE_LIMITER ; 
 unsigned int AL_UDMA_DEBUG_WRITE ; 
 scalar_t__ DMA_MAX_Q ; 
 scalar_t__ UDMA_TX ; 
 int /*<<< orphan*/  al_udma_regs_m2s_axi_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_comp_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_dwrr_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_feature_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_general_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_q_print (struct al_udma*,scalar_t__) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_rate_limiter_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_rd_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_stat_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_m2s_stream_rate_limiter_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_axi_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_comp_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_feature_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_general_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_q_print (struct al_udma*,scalar_t__) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_rd_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_stat_print (struct al_udma*) ; 
 int /*<<< orphan*/  al_udma_regs_s2m_wr_print (struct al_udma*) ; 

void al_udma_regs_print(struct al_udma *udma, unsigned int mask)
{
	uint32_t i;

	if (!udma)
		return;

	if (udma->type == UDMA_TX) {
		if (mask & AL_UDMA_DEBUG_AXI)
			al_udma_regs_m2s_axi_print(udma);
		if (mask & AL_UDMA_DEBUG_GENERAL)
			al_udma_regs_m2s_general_print(udma);
		if (mask & AL_UDMA_DEBUG_READ)
			al_udma_regs_m2s_rd_print(udma);
		if (mask & AL_UDMA_DEBUG_DWRR)
			al_udma_regs_m2s_dwrr_print(udma);
		if (mask & AL_UDMA_DEBUG_RATE_LIMITER)
			al_udma_regs_m2s_rate_limiter_print(udma);
		if (mask & AL_UDMA_DEBUG_STREAM_RATE_LIMITER)
			al_udma_regs_m2s_stream_rate_limiter_print(udma);
		if (mask & AL_UDMA_DEBUG_COMP)
			al_udma_regs_m2s_comp_print(udma);
		if (mask & AL_UDMA_DEBUG_STAT)
			al_udma_regs_m2s_stat_print(udma);
		if (mask & AL_UDMA_DEBUG_FEATURE)
			al_udma_regs_m2s_feature_print(udma);
		for (i = 0; i < DMA_MAX_Q; i++) {
			if (mask & AL_UDMA_DEBUG_QUEUE(i))
				al_udma_regs_m2s_q_print(udma, i);
		}
	} else {
		if (mask & AL_UDMA_DEBUG_AXI)
			al_udma_regs_s2m_axi_print(udma);
		if (mask & AL_UDMA_DEBUG_GENERAL)
			al_udma_regs_s2m_general_print(udma);
		if (mask & AL_UDMA_DEBUG_READ)
			al_udma_regs_s2m_rd_print(udma);
		if (mask & AL_UDMA_DEBUG_WRITE)
			al_udma_regs_s2m_wr_print(udma);
		if (mask & AL_UDMA_DEBUG_COMP)
			al_udma_regs_s2m_comp_print(udma);
		if (mask & AL_UDMA_DEBUG_STAT)
			al_udma_regs_s2m_stat_print(udma);
		if (mask & AL_UDMA_DEBUG_FEATURE)
			al_udma_regs_s2m_feature_print(udma);
		for (i = 0; i < DMA_MAX_Q; i++) {
			if (mask & AL_UDMA_DEBUG_QUEUE(i))
				al_udma_regs_s2m_q_print(udma, i);
		}
	}
}