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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHI_MSG_VECTOR_T ;
typedef  scalar_t__ VCHI_FLAGS_T ;
typedef  int /*<<< orphan*/  VCHIQ_ELEMENT_T ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ SHIM_SERVICE_T ;

/* Variables and functions */
 scalar_t__ VCHI_FLAGS_BLOCK_UNTIL_QUEUED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  vchiq_queue_message (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_status_to_vchi (int /*<<< orphan*/ ) ; 

int32_t vchi_msg_queuev(VCHI_SERVICE_HANDLE_T handle,
	VCHI_MSG_VECTOR_T *vector,
	uint32_t count,
	VCHI_FLAGS_T flags,
	void *msg_handle)
{
	SHIM_SERVICE_T *service = (SHIM_SERVICE_T *)handle;

	(void)msg_handle;

	WARN_ON(flags != VCHI_FLAGS_BLOCK_UNTIL_QUEUED);

	return vchiq_status_to_vchi(vchiq_queue_message(service->handle,
		(const VCHIQ_ELEMENT_T *)vector, count));
}