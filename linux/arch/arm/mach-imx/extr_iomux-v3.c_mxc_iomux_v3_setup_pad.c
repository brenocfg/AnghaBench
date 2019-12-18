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
typedef  int iomux_v3_cfg_t ;

/* Variables and functions */
 int MUX_CTRL_OFS_MASK ; 
 int MUX_CTRL_OFS_SHIFT ; 
 int MUX_MODE_MASK ; 
 int MUX_MODE_SHIFT ; 
 int MUX_PAD_CTRL_MASK ; 
 int MUX_PAD_CTRL_OFS_MASK ; 
 int MUX_PAD_CTRL_OFS_SHIFT ; 
 int MUX_PAD_CTRL_SHIFT ; 
 int MUX_SEL_INPUT_MASK ; 
 int MUX_SEL_INPUT_OFS_MASK ; 
 int MUX_SEL_INPUT_OFS_SHIFT ; 
 int MUX_SEL_INPUT_SHIFT ; 
 int NO_PAD_CTRL ; 
 int base ; 
 int /*<<< orphan*/  imx_writel (int,int) ; 

int mxc_iomux_v3_setup_pad(iomux_v3_cfg_t pad)
{
	u32 mux_ctrl_ofs = (pad & MUX_CTRL_OFS_MASK) >> MUX_CTRL_OFS_SHIFT;
	u32 mux_mode = (pad & MUX_MODE_MASK) >> MUX_MODE_SHIFT;
	u32 sel_input_ofs = (pad & MUX_SEL_INPUT_OFS_MASK) >> MUX_SEL_INPUT_OFS_SHIFT;
	u32 sel_input = (pad & MUX_SEL_INPUT_MASK) >> MUX_SEL_INPUT_SHIFT;
	u32 pad_ctrl_ofs = (pad & MUX_PAD_CTRL_OFS_MASK) >> MUX_PAD_CTRL_OFS_SHIFT;
	u32 pad_ctrl = (pad & MUX_PAD_CTRL_MASK) >> MUX_PAD_CTRL_SHIFT;

	if (mux_ctrl_ofs)
		imx_writel(mux_mode, base + mux_ctrl_ofs);

	if (sel_input_ofs)
		imx_writel(sel_input, base + sel_input_ofs);

	if (!(pad_ctrl & NO_PAD_CTRL) && pad_ctrl_ofs)
		imx_writel(pad_ctrl, base + pad_ctrl_ofs);

	return 0;
}