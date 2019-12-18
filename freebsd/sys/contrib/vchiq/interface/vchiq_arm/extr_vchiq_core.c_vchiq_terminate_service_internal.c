#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_8__ {int /*<<< orphan*/  remoteport; int /*<<< orphan*/  localport; TYPE_1__* state; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_POLL_REMOVE ; 
 int /*<<< orphan*/  mark_service_closing (TYPE_2__*) ; 
 int /*<<< orphan*/  request_poll (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vchiq_terminate_service_internal(VCHIQ_SERVICE_T *service)
{
	VCHIQ_STATE_T *state = service->state;

	vchiq_log_info(vchiq_core_log_level, "%d: tsi - (%d<->%d)",
		state->id, service->localport, service->remoteport);

	mark_service_closing(service);

	/* Mark the service for removal by the slot handler */
	request_poll(state, service, VCHIQ_POLL_REMOVE);
}