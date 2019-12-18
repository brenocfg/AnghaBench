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
struct TYPE_2__ {int /*<<< orphan*/  vsi_num; } ;
struct ixl_vf {TYPE_1__ vsi; } ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VSILAN_QTABLE (int,int /*<<< orphan*/ ) ; 
 int I40E_VSILAN_QTABLE_QINDEX_0_MASK ; 
 int I40E_VSILAN_QTABLE_QINDEX_1_SHIFT ; 
 int i40e_read_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_write_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixl_vf_map_vsi_queue(struct i40e_hw *hw, struct ixl_vf *vf, int qnum,
    uint32_t val)
{
	uint32_t qtable;
	int index, shift;

	/*
	 * Two queues are mapped in a single register, so we have to do some
	 * gymnastics to convert the queue number into a register index and
	 * shift.
	 */
	index = qnum / 2;
	shift = (qnum % 2) * I40E_VSILAN_QTABLE_QINDEX_1_SHIFT;

	qtable = i40e_read_rx_ctl(hw, I40E_VSILAN_QTABLE(index, vf->vsi.vsi_num));
	qtable &= ~(I40E_VSILAN_QTABLE_QINDEX_0_MASK << shift);
	qtable |= val << shift;
	i40e_write_rx_ctl(hw, I40E_VSILAN_QTABLE(index, vf->vsi.vsi_num), qtable);
}