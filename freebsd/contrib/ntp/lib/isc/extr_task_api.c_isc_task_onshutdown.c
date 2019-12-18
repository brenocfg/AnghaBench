#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_taskaction_t ;
struct TYPE_7__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_task_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* onshutdown ) (TYPE_2__*,int /*<<< orphan*/ ,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCAPI_TASK_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,void const*) ; 

isc_result_t
isc_task_onshutdown(isc_task_t *task, isc_taskaction_t action, const void *arg)
{
	REQUIRE(ISCAPI_TASK_VALID(task));

	return (task->methods->onshutdown(task, action, arg));
}