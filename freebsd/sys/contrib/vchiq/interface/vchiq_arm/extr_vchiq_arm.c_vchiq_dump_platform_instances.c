#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int unused_service; TYPE_3__** services; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
struct TYPE_6__ {scalar_t__ callback; } ;
struct TYPE_8__ {TYPE_4__* instance; TYPE_1__ base; } ;
typedef  TYPE_3__ VCHIQ_SERVICE_T ;
typedef  TYPE_4__* VCHIQ_INSTANCE_T ;
struct TYPE_9__ {int mark; int pid; int completion_insert; int completion_remove; scalar_t__ connected; } ;

/* Variables and functions */
 int MAX_COMPLETIONS ; 
 scalar_t__ service_callback ; 
 int snprintf (char*,int,char*,unsigned int,int,char*,int,int) ; 
 int /*<<< orphan*/  vchiq_dump (void*,char*,int) ; 
 TYPE_2__* vchiq_get_state () ; 

void
vchiq_dump_platform_instances(void *dump_context)
{
	VCHIQ_STATE_T *state = vchiq_get_state();
	char buf[80];
	int len;
	int i;

	/* There is no list of instances, so instead scan all services,
		marking those that have been dumped. */

	for (i = 0; i < state->unused_service; i++) {
		VCHIQ_SERVICE_T *service = state->services[i];
		VCHIQ_INSTANCE_T instance;

		if (service && (service->base.callback == service_callback)) {
			instance = service->instance;
			if (instance)
				instance->mark = 0;
		}
	}

	for (i = 0; i < state->unused_service; i++) {
		VCHIQ_SERVICE_T *service = state->services[i];
		VCHIQ_INSTANCE_T instance;

		if (service && (service->base.callback == service_callback)) {
			instance = service->instance;
			if (instance && !instance->mark) {
				len = snprintf(buf, sizeof(buf),
					"Instance %x: pid %d,%s completions "
						"%d/%d",
					(unsigned int)instance, instance->pid,
					instance->connected ? " connected, " :
						"",
					instance->completion_insert -
						instance->completion_remove,
					MAX_COMPLETIONS);

				vchiq_dump(dump_context, buf, len + 1);

				instance->mark = 1;
			}
		}
	}
}