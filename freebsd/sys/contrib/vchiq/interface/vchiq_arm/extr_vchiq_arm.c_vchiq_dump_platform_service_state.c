#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {scalar_t__ callback; scalar_t__ userdata; } ;
struct TYPE_6__ {TYPE_1__ base; scalar_t__ instance; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
struct TYPE_7__ {int msg_insert; int msg_remove; scalar_t__ dequeue_pending; scalar_t__ is_vchi; } ;
typedef  TYPE_3__ USER_SERVICE_T ;

/* Variables and functions */
 int MSG_QUEUE_SIZE ; 
 scalar_t__ service_callback ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vchiq_dump (void*,char*,int) ; 

void
vchiq_dump_platform_service_state(void *dump_context, VCHIQ_SERVICE_T *service)
{
	USER_SERVICE_T *user_service = (USER_SERVICE_T *)service->base.userdata;
	char buf[80];
	int len;

	len = snprintf(buf, sizeof(buf), "  instance %x",
		(unsigned int)service->instance);

	if ((service->base.callback == service_callback) &&
		user_service->is_vchi) {
		len += snprintf(buf + len, sizeof(buf) - len,
			", %d/%d messages",
			user_service->msg_insert - user_service->msg_remove,
			MSG_QUEUE_SIZE);

		if (user_service->dequeue_pending)
			len += snprintf(buf + len, sizeof(buf) - len,
				" (dequeue pending)");
	}

	vchiq_dump(dump_context, buf, len + 1);
}