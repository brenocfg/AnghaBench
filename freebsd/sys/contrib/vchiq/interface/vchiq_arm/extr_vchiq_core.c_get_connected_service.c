#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int unused_service; TYPE_2__** services; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_7__ {scalar_t__ srvstate; unsigned int remoteport; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SRVSTATE_OPEN ; 
 int /*<<< orphan*/  lock_service (TYPE_2__*) ; 

__attribute__((used)) static VCHIQ_SERVICE_T *
get_connected_service(VCHIQ_STATE_T *state, unsigned int port)
{
	int i;
	for (i = 0; i < state->unused_service; i++) {
		VCHIQ_SERVICE_T *service = state->services[i];
		if (service && (service->srvstate == VCHIQ_SRVSTATE_OPEN)
			&& (service->remoteport == port)) {
			lock_service(service);
			return service;
		}
	}
	return NULL;
}