#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/ * VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_12__ {int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; TYPE_3__* userdata; int /*<<< orphan*/  callback; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_PARAMS_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;
struct TYPE_11__ {int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; } ;
struct TYPE_14__ {TYPE_1__ version; int /*<<< orphan*/  service_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_3__ SHIM_SERVICE_T ;
typedef  TYPE_4__ SERVICE_CREATION_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* service_alloc (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  service_free (TYPE_3__*) ; 
 int /*<<< orphan*/  shim_callback ; 
 scalar_t__ vchiq_add_service (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

int32_t vchi_service_create(VCHI_INSTANCE_T instance_handle,
	SERVICE_CREATION_T *setup,
	VCHI_SERVICE_HANDLE_T *handle)
{
	VCHIQ_INSTANCE_T instance = (VCHIQ_INSTANCE_T)instance_handle;
	SHIM_SERVICE_T *service = service_alloc(instance, setup);

	*handle = (VCHI_SERVICE_HANDLE_T)service;

	if (service) {
		VCHIQ_SERVICE_PARAMS_T params;
		VCHIQ_STATUS_T status;

		memset(&params, 0, sizeof(params));
		params.fourcc = setup->service_id;
		params.callback = shim_callback;
		params.userdata = service;
		params.version = setup->version.version;
		params.version_min = setup->version.version_min;
		status = vchiq_add_service(instance, &params, &service->handle);

		if (status != VCHIQ_SUCCESS) {
			service_free(service);
			service = NULL;
			*handle = NULL;
		}
	}

	return (service != NULL) ? 0 : -1;
}