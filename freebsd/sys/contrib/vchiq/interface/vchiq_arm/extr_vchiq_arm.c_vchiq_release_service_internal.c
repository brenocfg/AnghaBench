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
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_release_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 

VCHIQ_STATUS_T
vchiq_release_service_internal(VCHIQ_SERVICE_T *service)
{
	return vchiq_release_internal(service->state, service);
}