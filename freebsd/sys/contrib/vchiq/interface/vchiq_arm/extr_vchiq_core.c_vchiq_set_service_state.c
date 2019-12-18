#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t srvstate; int /*<<< orphan*/  localport; TYPE_1__* state; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/ * srvstate_names ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vchiq_set_service_state(VCHIQ_SERVICE_T *service, int newstate)
{
	vchiq_log_info(vchiq_core_log_level, "%d: srv:%d %s->%s",
		service->state->id, service->localport,
		srvstate_names[service->srvstate],
		srvstate_names[newstate]);
	service->srvstate = newstate;
}