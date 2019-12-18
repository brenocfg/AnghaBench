#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int num_tx_queues; int /*<<< orphan*/  vsi_num; } ;
struct ixl_vf {int /*<<< orphan*/  qtag; TYPE_1__ vsi; int /*<<< orphan*/  vf_num; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VPLAN_MAPENA (int /*<<< orphan*/ ) ; 
 int I40E_VPLAN_MAPENA_TXRX_ENA_MASK ; 
 int /*<<< orphan*/  I40E_VPLAN_QTABLE (int,int /*<<< orphan*/ ) ; 
 int I40E_VPLAN_QTABLE_QINDEX_MASK ; 
 int I40E_VPLAN_QTABLE_QINDEX_SHIFT ; 
 int /*<<< orphan*/  I40E_VSILAN_QBASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_VSILAN_QBASE_VSIQTABLE_ENA_MASK ; 
 int I40E_VSILAN_QTABLE_QINDEX_0_MASK ; 
 int IXL_MAX_VSI_QUEUES ; 
 int /*<<< orphan*/  i40e_write_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int ixl_pf_qidx_from_vsi_qidx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ixl_vf_map_vsi_queue (struct i40e_hw*,struct ixl_vf*,int,int) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixl_vf_map_queues(struct ixl_pf *pf, struct ixl_vf *vf)
{
	struct i40e_hw *hw;
	uint32_t qtable;
	int i;

	hw = &pf->hw;

	/*
	 * Contiguous mappings aren't actually supported by the hardware,
	 * so we have to use non-contiguous mappings.
	 */
	i40e_write_rx_ctl(hw, I40E_VSILAN_QBASE(vf->vsi.vsi_num),
	     I40E_VSILAN_QBASE_VSIQTABLE_ENA_MASK);

	/* Enable LAN traffic on this VF */
	wr32(hw, I40E_VPLAN_MAPENA(vf->vf_num),
	    I40E_VPLAN_MAPENA_TXRX_ENA_MASK);

	/* Program index of each VF queue into PF queue space
	 * (This is only needed if QTABLE is enabled) */
	for (i = 0; i < vf->vsi.num_tx_queues; i++) {
		qtable = ixl_pf_qidx_from_vsi_qidx(&vf->qtag, i) <<
		    I40E_VPLAN_QTABLE_QINDEX_SHIFT;

		wr32(hw, I40E_VPLAN_QTABLE(i, vf->vf_num), qtable);
	}
	for (; i < IXL_MAX_VSI_QUEUES; i++)
		wr32(hw, I40E_VPLAN_QTABLE(i, vf->vf_num),
		    I40E_VPLAN_QTABLE_QINDEX_MASK);

	/* Map queues allocated to VF to its VSI;
	 * This mapping matches the VF-wide mapping since the VF
	 * is only given a single VSI */
	for (i = 0; i < vf->vsi.num_tx_queues; i++)
		ixl_vf_map_vsi_queue(hw, vf, i,
		    ixl_pf_qidx_from_vsi_qidx(&vf->qtag, i));

	/* Set rest of VSI queues as unused. */
	for (; i < IXL_MAX_VSI_QUEUES; i++)
		ixl_vf_map_vsi_queue(hw, vf, i,
		    I40E_VSILAN_QTABLE_QINDEX_0_MASK);

	ixl_flush(hw);
}