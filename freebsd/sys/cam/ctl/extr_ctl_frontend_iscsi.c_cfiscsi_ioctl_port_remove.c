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
typedef  int /*<<< orphan*/  uint16_t ;
struct ctl_req {void* status; int /*<<< orphan*/  error_str; int /*<<< orphan*/  args_nvl; } ;
struct cfiscsi_target {int /*<<< orphan*/  ct_port; int /*<<< orphan*/  ct_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_TARGET_STATE_DYING ; 
 void* CTL_LUN_ERROR ; 
 void* CTL_LUN_OK ; 
 int /*<<< orphan*/  cfiscsi_softc ; 
 struct cfiscsi_target* cfiscsi_target_find (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfiscsi_target_release (struct cfiscsi_target*) ; 
 int /*<<< orphan*/  ctl_port_offline (int /*<<< orphan*/ *) ; 
 char* dnvlist_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cfiscsi_ioctl_port_remove(struct ctl_req *req)
{
	struct cfiscsi_target *ct;
	const char *target, *val;
	uint16_t tag;

	target = dnvlist_get_string(req->args_nvl, "cfiscsi_target", NULL);
	val = dnvlist_get_string(req->args_nvl, "cfiscsi_portal_group_tag",
	    NULL);

	if (target == NULL || val == NULL) {
		req->status = CTL_LUN_ERROR;
		snprintf(req->error_str, sizeof(req->error_str),
		    "Missing required argument");
		return;
	}

	tag = strtoul(val, NULL, 0);
	ct = cfiscsi_target_find(&cfiscsi_softc, target, tag);
	if (ct == NULL) {
		req->status = CTL_LUN_ERROR;
		snprintf(req->error_str, sizeof(req->error_str),
		    "can't find target \"%s\"", target);
		return;
	}

	ct->ct_state = CFISCSI_TARGET_STATE_DYING;
	ctl_port_offline(&ct->ct_port);
	cfiscsi_target_release(ct);
	cfiscsi_target_release(ct);
	req->status = CTL_LUN_OK;
}