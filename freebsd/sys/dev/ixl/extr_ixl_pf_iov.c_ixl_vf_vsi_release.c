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
struct ixl_vsi {int /*<<< orphan*/  seid; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_aq_delete_element (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ixl_vf_vsi_release(struct ixl_pf *pf, struct ixl_vsi *vsi)
{
	struct i40e_hw *hw;

	hw = &pf->hw;

	if (vsi->seid == 0)
		return;

	i40e_aq_delete_element(hw, vsi->seid, NULL);
}