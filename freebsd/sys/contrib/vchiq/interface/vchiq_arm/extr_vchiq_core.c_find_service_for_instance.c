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
struct TYPE_4__ {scalar_t__ srvstate; scalar_t__ handle; scalar_t__ instance; scalar_t__ ref_count; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;
typedef  scalar_t__ VCHIQ_SERVICE_HANDLE_T ;
typedef  scalar_t__ VCHIQ_INSTANCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VCHIQ_SRVSTATE_FREE ; 
 TYPE_1__* handle_to_service (scalar_t__) ; 
 int /*<<< orphan*/  service_spinlock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 

VCHIQ_SERVICE_T *
find_service_for_instance(VCHIQ_INSTANCE_T instance,
	VCHIQ_SERVICE_HANDLE_T handle) {
	VCHIQ_SERVICE_T *service;

	spin_lock(&service_spinlock);
	service = handle_to_service(handle);
	if (service && (service->srvstate != VCHIQ_SRVSTATE_FREE) &&
		(service->handle == handle) &&
		(service->instance == instance)) {
		BUG_ON(service->ref_count == 0);
		service->ref_count++;
	} else
		service = NULL;
	spin_unlock(&service_spinlock);

	if (!service)
		vchiq_log_info(vchiq_core_log_level,
			"Invalid service handle 0x%x", handle);

	return service;
}