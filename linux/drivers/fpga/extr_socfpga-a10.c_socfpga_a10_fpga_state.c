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
typedef  int u32 ;
struct fpga_manager {struct a10_fpga_priv* priv; } ;
struct a10_fpga_priv {int dummy; } ;
typedef  enum fpga_mgr_states { ____Placeholder_fpga_mgr_states } fpga_mgr_states ;

/* Variables and functions */
 int A10_FPGAMGR_IMGCFG_STAT_F2S_CRC_ERROR ; 
 int A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN ; 
 int A10_FPGAMGR_IMGCFG_STAT_F2S_PR_READY ; 
 int A10_FPGAMGR_IMGCFG_STAT_F2S_USERMODE ; 
 int FPGA_MGR_STATE_OPERATING ; 
 int FPGA_MGR_STATE_RESET ; 
 int FPGA_MGR_STATE_UNKNOWN ; 
 int FPGA_MGR_STATE_WRITE ; 
 int FPGA_MGR_STATE_WRITE_COMPLETE_ERR ; 
 int socfpga_a10_fpga_read_stat (struct a10_fpga_priv*) ; 

__attribute__((used)) static enum fpga_mgr_states socfpga_a10_fpga_state(struct fpga_manager *mgr)
{
	struct a10_fpga_priv *priv = mgr->priv;
	u32 reg = socfpga_a10_fpga_read_stat(priv);

	if (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_USERMODE)
		return FPGA_MGR_STATE_OPERATING;

	if (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_PR_READY)
		return FPGA_MGR_STATE_WRITE;

	if (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_CRC_ERROR)
		return FPGA_MGR_STATE_WRITE_COMPLETE_ERR;

	if ((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN) == 0)
		return FPGA_MGR_STATE_RESET;

	return FPGA_MGR_STATE_UNKNOWN;
}