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
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ SHIM_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vchiu_queue_pop (int /*<<< orphan*/ *) ; 

int32_t vchi_msg_remove(VCHI_SERVICE_HANDLE_T handle)
{
	SHIM_SERVICE_T *service = (SHIM_SERVICE_T *)handle;
	VCHIQ_HEADER_T *header;

	header = vchiu_queue_pop(&service->queue);

	vchiq_release_message(service->handle, header);

	return 0;
}