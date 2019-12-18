#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  get_link_info; } ;
struct i40e_hw {TYPE_3__ phy; } ;
struct ixl_pf {scalar_t__ advertised_speed; int /*<<< orphan*/  link_up; TYPE_4__ vsi; struct i40e_hw hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {TYPE_1__ params; } ;
struct i40e_arq_event_info {TYPE_2__ desc; } ;
struct i40e_aqc_get_link_status {int link_info; int an_info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int I40E_AQ_LINK_UP ; 
 int I40E_AQ_MEDIA_AVAILABLE ; 
 int I40E_AQ_QUALIFIED_MODULE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i40e_get_link_status (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 

void
ixl_link_event(struct ixl_pf *pf, struct i40e_arq_event_info *e)
{
	struct i40e_hw *hw = &pf->hw; 
	device_t dev = iflib_get_dev(pf->vsi.ctx);
	struct i40e_aqc_get_link_status *status =
	    (struct i40e_aqc_get_link_status *)&e->desc.params.raw;

	/* Request link status from adapter */
	hw->phy.get_link_info = TRUE;
	i40e_get_link_status(hw, &pf->link_up);

	/* Print out message if an unqualified module is found */
	if ((status->link_info & I40E_AQ_MEDIA_AVAILABLE) &&
	    (pf->advertised_speed) &&
	    (!(status->an_info & I40E_AQ_QUALIFIED_MODULE)) &&
	    (!(status->link_info & I40E_AQ_LINK_UP)))
		device_printf(dev, "Link failed because "
		    "an unqualified module was detected!\n");

	/* OS link info is updated elsewhere */
}