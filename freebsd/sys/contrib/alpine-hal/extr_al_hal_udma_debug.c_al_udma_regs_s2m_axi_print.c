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
 int /*<<< orphan*/  al_dbg (char*) ; 
 int /*<<< orphan*/  axi_s2m ; 
 int /*<<< orphan*/  comp_wr_cfg_1 ; 
 int /*<<< orphan*/  comp_wr_cfg_2 ; 
 int /*<<< orphan*/  data_wr_cfg ; 
 int /*<<< orphan*/  data_wr_cfg_1 ; 
 int /*<<< orphan*/  data_wr_cfg_2 ; 
 int /*<<< orphan*/  desc_rd_cfg_3 ; 
 int /*<<< orphan*/  desc_rd_cfg_4 ; 
 int /*<<< orphan*/  desc_rd_cfg_5 ; 
 int /*<<< orphan*/  desc_wr_cfg_1 ; 
 int /*<<< orphan*/  ostand_cfg_rd ; 
 int /*<<< orphan*/  ostand_cfg_wr ; 
 int /*<<< orphan*/  s2m ; 

__attribute__((used)) static void al_udma_regs_s2m_axi_print(struct al_udma *udma)
{
	al_dbg("S2M AXI regs:\n");
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, data_wr_cfg_1);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, data_wr_cfg_2);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, desc_rd_cfg_4);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, desc_rd_cfg_5);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, comp_wr_cfg_1);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, comp_wr_cfg_2);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, data_wr_cfg);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, desc_rd_cfg_3);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, desc_wr_cfg_1);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, ostand_cfg_rd);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, axi_s2m, ostand_cfg_wr);
}