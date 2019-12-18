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
struct TYPE_2__ {int /*<<< orphan*/  group_id; int /*<<< orphan*/  ifname; int /*<<< orphan*/  attached; } ;
union fst_event_extra {TYPE_1__ iface_state; } ;
struct fst_iface {int dummy; } ;
typedef  int /*<<< orphan*/  extra ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_FST_IFACE_STATE_CHANGED ; 
 int /*<<< orphan*/  FST_INVALID_SESSION_ID ; 
 int /*<<< orphan*/  fst_ctrl_iface_notify (struct fst_iface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union fst_event_extra*) ; 
 int /*<<< orphan*/  fst_iface_get_group_id (struct fst_iface*) ; 
 int /*<<< orphan*/  fst_iface_get_name (struct fst_iface*) ; 
 int /*<<< orphan*/  os_memset (union fst_event_extra*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fst_ctrl_iface_on_iface_state_changed(struct fst_iface *i,
						  Boolean attached)
{
	union fst_event_extra extra;

	os_memset(&extra, 0, sizeof(extra));
	extra.iface_state.attached = attached;
	os_strlcpy(extra.iface_state.ifname, fst_iface_get_name(i),
		   sizeof(extra.iface_state.ifname));
	os_strlcpy(extra.iface_state.group_id, fst_iface_get_group_id(i),
		   sizeof(extra.iface_state.group_id));

	fst_ctrl_iface_notify(i, FST_INVALID_SESSION_ID,
			      EVENT_FST_IFACE_STATE_CHANGED, &extra);
}