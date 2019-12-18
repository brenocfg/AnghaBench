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
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;
struct TYPE_8__ {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback; } ;
struct TYPE_7__ {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ SHIM_SERVICE_T ;
typedef  TYPE_2__ SERVICE_CREATION_T ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vchiu_queue_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static SHIM_SERVICE_T *service_alloc(VCHIQ_INSTANCE_T instance,
	SERVICE_CREATION_T *setup)
{
	SHIM_SERVICE_T *service = kzalloc(sizeof(SHIM_SERVICE_T), GFP_KERNEL);

	(void)instance;

	if (service) {
		if (vchiu_queue_init(&service->queue, 64)) {
			service->callback = setup->callback;
			service->callback_param = setup->callback_param;
		} else {
			kfree(service);
			service = NULL;
		}
	}

	return service;
}