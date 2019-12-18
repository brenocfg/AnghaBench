#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum vc_suspend_status { ____Placeholder_vc_suspend_status } vc_suspend_status ;
typedef  enum vc_resume_status { ____Placeholder_vc_resume_status } vc_resume_status ;
struct TYPE_10__ {int unused_service; TYPE_3__** services; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
struct TYPE_9__ {int fourcc; } ;
struct TYPE_11__ {int service_use_count; scalar_t__ srvstate; int client_id; TYPE_1__ base; } ;
typedef  TYPE_3__ VCHIQ_SERVICE_T ;
struct TYPE_12__ {int vc_suspend_state; int vc_resume_state; int peer_use_count; int videocore_use_count; int /*<<< orphan*/  susp_res_lock; } ;
typedef  TYPE_4__ VCHIQ_ARM_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_FOURCC_AS_4CHARS (int) ; 
 scalar_t__ VCHIQ_SRVSTATE_FREE ; 
 int VC_RESUME_NUM_OFFSET ; 
 int VC_SUSPEND_NUM_OFFSET ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int* resume_state_names ; 
 int* suspend_state_names ; 
 int /*<<< orphan*/  vchiq_dump_platform_use_state (TYPE_2__*) ; 
 int /*<<< orphan*/  vchiq_log_warning (int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_4__* vchiq_platform_get_arm_state (TYPE_2__*) ; 
 int /*<<< orphan*/  vchiq_susp_log_level ; 

void
vchiq_dump_service_use_state(VCHIQ_STATE_T *state)
{
	VCHIQ_ARM_STATE_T *arm_state = vchiq_platform_get_arm_state(state);
	int i, j = 0;
	/* Only dump 64 services */
	static const int local_max_services = 64;
	/* If there's more than 64 services, only dump ones with
	 * non-zero counts */
	int only_nonzero = 0;
	static const char *nz = "<-- preventing suspend";

	enum vc_suspend_status vc_suspend_state;
	enum vc_resume_status  vc_resume_state;
	int peer_count;
	int vc_use_count;
	int active_services;
	struct service_data_struct {
		int fourcc;
		int clientid;
		int use_count;
	} service_data[local_max_services];

	if (!arm_state)
		return;

	read_lock_bh(&arm_state->susp_res_lock);
	vc_suspend_state = arm_state->vc_suspend_state;
	vc_resume_state  = arm_state->vc_resume_state;
	peer_count = arm_state->peer_use_count;
	vc_use_count = arm_state->videocore_use_count;
	active_services = state->unused_service;
	if (active_services > local_max_services)
		only_nonzero = 1;

	for (i = 0; (i < active_services) && (j < local_max_services); i++) {
		VCHIQ_SERVICE_T *service_ptr = state->services[i];
		if (!service_ptr)
			continue;

		if (only_nonzero && !service_ptr->service_use_count)
			continue;

		if (service_ptr->srvstate != VCHIQ_SRVSTATE_FREE) {
			service_data[j].fourcc = service_ptr->base.fourcc;
			service_data[j].clientid = service_ptr->client_id;
			service_data[j++].use_count = service_ptr->
							service_use_count;
		}
	}

	read_unlock_bh(&arm_state->susp_res_lock);

	vchiq_log_warning(vchiq_susp_log_level,
		"-- Videcore suspend state: %s --",
		suspend_state_names[vc_suspend_state + VC_SUSPEND_NUM_OFFSET]);
	vchiq_log_warning(vchiq_susp_log_level,
		"-- Videcore resume state: %s --",
		resume_state_names[vc_resume_state + VC_RESUME_NUM_OFFSET]);

	if (only_nonzero)
		vchiq_log_warning(vchiq_susp_log_level, "Too many active "
			"services (%d).  Only dumping up to first %d services "
			"with non-zero use-count", active_services,
			local_max_services);

	for (i = 0; i < j; i++) {
		vchiq_log_warning(vchiq_susp_log_level,
			"----- %c%c%c%c:%d service count %d %s",
			VCHIQ_FOURCC_AS_4CHARS(service_data[i].fourcc),
			service_data[i].clientid,
			service_data[i].use_count,
			service_data[i].use_count ? nz : "");
	}
	vchiq_log_warning(vchiq_susp_log_level,
		"----- VCHIQ use count count %d", peer_count);
	vchiq_log_warning(vchiq_susp_log_level,
		"--- Overall vchiq instance use count %d", vc_use_count);

	vchiq_dump_platform_use_state(state);
}