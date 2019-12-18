#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
typedef  int VCHI_SERVICE_OPTION_T ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_OPTION_T ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ SHIM_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_SERVICE_OPTION_SYNCHRONOUS ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_OPTION_TRACE ; 
#define  VCHI_SERVICE_OPTION_SYNCHRONOUS 129 
#define  VCHI_SERVICE_OPTION_TRACE 128 
 int /*<<< orphan*/  vchiq_set_service_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vchiq_status_to_vchi (int /*<<< orphan*/ ) ; 

int32_t vchi_service_set_option(const VCHI_SERVICE_HANDLE_T handle,
				VCHI_SERVICE_OPTION_T option,
				int value)
{
	int32_t ret = -1;
	SHIM_SERVICE_T *service = (SHIM_SERVICE_T *)handle;
	VCHIQ_SERVICE_OPTION_T vchiq_option;
	switch (option) {
	case VCHI_SERVICE_OPTION_TRACE:
		vchiq_option = VCHIQ_SERVICE_OPTION_TRACE;
		break;
	case VCHI_SERVICE_OPTION_SYNCHRONOUS:
		vchiq_option = VCHIQ_SERVICE_OPTION_SYNCHRONOUS;
		break;
	default:
		service = NULL;
		break;
	}
	if (service) {
		VCHIQ_STATUS_T status =
			vchiq_set_service_option(service->handle,
						vchiq_option,
						value);

		ret = vchiq_status_to_vchi(status);
	}
	return ret;
}