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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ixl_vf {int /*<<< orphan*/  num_mdd_events; } ;
struct i40e_hw {int pf_id; } ;
struct ixl_pf {int num_vfs; struct ixl_vf* vfs; int /*<<< orphan*/  dev; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_GL_MDET_RX ; 
 int I40E_GL_MDET_RX_EVENT_MASK ; 
 int I40E_GL_MDET_RX_EVENT_SHIFT ; 
 int I40E_GL_MDET_RX_FUNCTION_MASK ; 
 int I40E_GL_MDET_RX_FUNCTION_SHIFT ; 
 int I40E_GL_MDET_RX_QUEUE_MASK ; 
 int I40E_GL_MDET_RX_QUEUE_SHIFT ; 
 int I40E_GL_MDET_RX_VALID_MASK ; 
 int /*<<< orphan*/  I40E_PF_MDET_RX ; 
 int I40E_PF_MDET_RX_VALID_MASK ; 
 int /*<<< orphan*/  I40E_VP_MDET_RX (int) ; 
 int I40E_VP_MDET_RX_VALID_MASK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixl_handle_rx_mdd_event(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	device_t dev = pf->dev;
	struct ixl_vf *vf;
	bool mdd_detected = false;
	bool pf_mdd_detected = false;
	bool vf_mdd_detected = false;
	u16 queue;
	u8 pf_num, event;
	u8 pf_mdet_num, vp_mdet_num;
	u32 reg;

	/*
	 * GL_MDET_RX doesn't contain VF number information, unlike
	 * GL_MDET_TX.
	 */
	reg = rd32(hw, I40E_GL_MDET_RX);
	if (reg & I40E_GL_MDET_RX_VALID_MASK) {
		pf_num = (reg & I40E_GL_MDET_RX_FUNCTION_MASK) >>
		    I40E_GL_MDET_RX_FUNCTION_SHIFT;
		event = (reg & I40E_GL_MDET_RX_EVENT_MASK) >>
		    I40E_GL_MDET_RX_EVENT_SHIFT;
		queue = (reg & I40E_GL_MDET_RX_QUEUE_MASK) >>
		    I40E_GL_MDET_RX_QUEUE_SHIFT;
		wr32(hw, I40E_GL_MDET_RX, 0xffffffff);
		mdd_detected = true;
	}

	if (!mdd_detected)
		return;

	reg = rd32(hw, I40E_PF_MDET_RX);
	if (reg & I40E_PF_MDET_RX_VALID_MASK) {
		wr32(hw, I40E_PF_MDET_RX, 0xFFFF);
		pf_mdet_num = hw->pf_id;
		pf_mdd_detected = true;
	}

	/* Check if MDD was caused by a VF */
	for (int i = 0; i < pf->num_vfs; i++) {
		vf = &(pf->vfs[i]);
		reg = rd32(hw, I40E_VP_MDET_RX(i));
		if (reg & I40E_VP_MDET_RX_VALID_MASK) {
			wr32(hw, I40E_VP_MDET_RX(i), 0xFFFF);
			vp_mdet_num = i;
			vf->num_mdd_events++;
			vf_mdd_detected = true;
		}
	}

	/* Print out an error message */
	if (vf_mdd_detected && pf_mdd_detected)
		device_printf(dev,
		    "Malicious Driver Detection event %d"
		    " on RX queue %d, pf number %d (PF-%d), (VF-%d)\n",
		    event, queue, pf_num, pf_mdet_num, vp_mdet_num);
	else if (vf_mdd_detected && !pf_mdd_detected)
		device_printf(dev,
		    "Malicious Driver Detection event %d"
		    " on RX queue %d, pf number %d, (VF-%d)\n",
		    event, queue, pf_num, vp_mdet_num);
	else if (!vf_mdd_detected && pf_mdd_detected)
		device_printf(dev,
		    "Malicious Driver Detection event %d"
		    " on RX queue %d, pf number %d (PF-%d)\n",
		    event, queue, pf_num, pf_mdet_num);
	/* Theoretically shouldn't happen */
	else
		device_printf(dev,
		    "RX Malicious Driver Detection event (unknown)\n");
}