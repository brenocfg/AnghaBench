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
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_5__ {scalar_t__ (* callback ) (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  handle; TYPE_2__* state; TYPE_1__ base; int /*<<< orphan*/  localport; } ;
typedef  TYPE_3__ VCHIQ_SERVICE_T ;
typedef  size_t VCHIQ_REASON_T ;
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_ERROR ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/ * reason_names ; 
 scalar_t__ stub1 (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vchiq_log_warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline VCHIQ_STATUS_T
make_service_callback(VCHIQ_SERVICE_T *service, VCHIQ_REASON_T reason,
	VCHIQ_HEADER_T *header, void *bulk_userdata)
{
	VCHIQ_STATUS_T status;
	vchiq_log_trace(vchiq_core_log_level, "%d: callback:%d (%s, %x, %x)",
		service->state->id, service->localport, reason_names[reason],
		(unsigned int)header, (unsigned int)bulk_userdata);
	status = service->base.callback(reason, header, service->handle,
		bulk_userdata);
	if (status == VCHIQ_ERROR) {
		vchiq_log_warning(vchiq_core_log_level,
			"%d: ignoring ERROR from callback to service %x",
			service->state->id, service->handle);
		status = VCHIQ_SUCCESS;
	}
	return status;
}