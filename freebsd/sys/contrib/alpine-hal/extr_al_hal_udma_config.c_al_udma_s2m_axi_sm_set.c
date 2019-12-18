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
struct al_udma_axi_submaster {int id; int cache_type; int burst; int used_ext; int bus_size; int qos; int prot; int max_beats; } ;

/* Variables and functions */
 int UDMA_AXI_S2M_COMP_WR_CFG_1_AWBURST_MASK ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_1_AWBURST_SHIFT ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_1_AWCACHE_MASK ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_1_AWCACHE_SHIFT ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_1_AWID_MASK ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_2_AWPROT_MASK ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_2_AWPROT_SHIFT ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_2_AWQOS_MASK ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_2_AWQOS_SHIFT ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_2_AWSIZE_MASK ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_2_AWSIZE_SHIFT ; 
 int UDMA_AXI_S2M_COMP_WR_CFG_2_AWUSER_MASK ; 
 int UDMA_AXI_S2M_DESC_WR_CFG_1_MAX_AXI_BEATS_MASK ; 
 int al_reg_read32 (int*) ; 
 int /*<<< orphan*/  al_reg_write32 (int*,int) ; 

__attribute__((used)) static int al_udma_s2m_axi_sm_set(struct al_udma_axi_submaster *s2m_sm,
				      uint32_t *cfg_1, uint32_t *cfg_2,
				      uint32_t *cfg_max_beats)
{
	uint32_t reg;
	reg = al_reg_read32(cfg_1);
	reg &= ~UDMA_AXI_S2M_COMP_WR_CFG_1_AWID_MASK;
	reg |= s2m_sm->id & UDMA_AXI_S2M_COMP_WR_CFG_1_AWID_MASK;
	reg &= ~UDMA_AXI_S2M_COMP_WR_CFG_1_AWCACHE_MASK;
	reg |= (s2m_sm->cache_type <<
			UDMA_AXI_S2M_COMP_WR_CFG_1_AWCACHE_SHIFT) &
		UDMA_AXI_S2M_COMP_WR_CFG_1_AWCACHE_MASK;
	reg &= ~UDMA_AXI_S2M_COMP_WR_CFG_1_AWBURST_MASK;
	reg |= (s2m_sm->burst << UDMA_AXI_S2M_COMP_WR_CFG_1_AWBURST_SHIFT) &
		UDMA_AXI_S2M_COMP_WR_CFG_1_AWBURST_MASK;
	al_reg_write32(cfg_1, reg);

	reg = al_reg_read32(cfg_2);
	reg &= ~UDMA_AXI_S2M_COMP_WR_CFG_2_AWUSER_MASK;
	reg |= s2m_sm->used_ext & UDMA_AXI_S2M_COMP_WR_CFG_2_AWUSER_MASK;
	reg &= ~UDMA_AXI_S2M_COMP_WR_CFG_2_AWSIZE_MASK;
	reg |= (s2m_sm->bus_size << UDMA_AXI_S2M_COMP_WR_CFG_2_AWSIZE_SHIFT) &
		UDMA_AXI_S2M_COMP_WR_CFG_2_AWSIZE_MASK;
	reg &= ~UDMA_AXI_S2M_COMP_WR_CFG_2_AWQOS_MASK;
	reg |= (s2m_sm->qos << UDMA_AXI_S2M_COMP_WR_CFG_2_AWQOS_SHIFT) &
		UDMA_AXI_S2M_COMP_WR_CFG_2_AWQOS_MASK;
	reg &= ~UDMA_AXI_S2M_COMP_WR_CFG_2_AWPROT_MASK;
	reg |= (s2m_sm->prot << UDMA_AXI_S2M_COMP_WR_CFG_2_AWPROT_SHIFT) &
		UDMA_AXI_S2M_COMP_WR_CFG_2_AWPROT_MASK;
	al_reg_write32(cfg_2, reg);

	reg = al_reg_read32(cfg_max_beats);
	reg &= ~UDMA_AXI_S2M_DESC_WR_CFG_1_MAX_AXI_BEATS_MASK;
	reg |= s2m_sm->max_beats &
			UDMA_AXI_S2M_DESC_WR_CFG_1_MAX_AXI_BEATS_MASK;
	al_reg_write32(cfg_max_beats, reg);

	return 0;
}