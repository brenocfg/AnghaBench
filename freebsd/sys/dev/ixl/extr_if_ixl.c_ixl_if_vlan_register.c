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
typedef  int u16 ;
struct ixl_vsi {int /*<<< orphan*/  num_vlans; struct i40e_hw* hw; } ;
struct ixl_pf {struct ixl_vsi vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct i40e_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_add_filter (struct ixl_vsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixl_if_vlan_register(if_ctx_t ctx, u16 vtag)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct i40e_hw	*hw = vsi->hw;

	if ((vtag == 0) || (vtag > 4095))	/* Invalid */
		return;

	++vsi->num_vlans;
	ixl_add_filter(vsi, hw->mac.addr, vtag);
}