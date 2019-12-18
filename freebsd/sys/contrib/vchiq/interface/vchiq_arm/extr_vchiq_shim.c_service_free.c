#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ SHIM_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  vchiu_queue_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void service_free(SHIM_SERVICE_T *service)
{
	if (service) {
		vchiu_queue_delete(&service->queue);
		kfree(service);
	}
}