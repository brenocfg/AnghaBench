#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int link_speed; int /*<<< orphan*/  link_status; } ;
struct TYPE_9__ {TYPE_5__ link_event; } ;
struct virtchnl_pf_event {TYPE_4__ event_data; int /*<<< orphan*/  severity; int /*<<< orphan*/  event; } ;
struct ixl_vf {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  link_active; } ;
struct TYPE_7__ {scalar_t__ link_speed; } ;
struct TYPE_8__ {TYPE_2__ link_info; } ;
struct i40e_hw {TYPE_3__ phy; } ;
struct ixl_pf {TYPE_1__ vsi; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum virtchnl_link_speed { ____Placeholder_virtchnl_link_speed } virtchnl_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  PF_EVENT_SEVERITY_INFO ; 
 int /*<<< orphan*/  VIRTCHNL_EVENT_LINK_CHANGE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_EVENT ; 
 int /*<<< orphan*/  ixl_send_vf_msg (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtchnl_pf_event*,int) ; 

__attribute__((used)) static void
ixl_notify_vf_link_state(struct ixl_pf *pf, struct ixl_vf *vf)
{
	struct virtchnl_pf_event event;
	struct i40e_hw *hw;

	hw = &pf->hw;
	event.event = VIRTCHNL_EVENT_LINK_CHANGE;
	event.severity = PF_EVENT_SEVERITY_INFO;
	event.event_data.link_event.link_status = pf->vsi.link_active;
	event.event_data.link_event.link_speed =
		(enum virtchnl_link_speed)hw->phy.link_info.link_speed;

	ixl_send_vf_msg(pf, vf, VIRTCHNL_OP_EVENT, I40E_SUCCESS, &event,
			sizeof(event));
}