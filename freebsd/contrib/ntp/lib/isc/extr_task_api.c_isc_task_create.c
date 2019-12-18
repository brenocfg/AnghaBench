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
struct TYPE_7__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_taskmgr_t ;
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* taskcreate ) (TYPE_2__*,unsigned int,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int ISCAPI_TASKMGR_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned int,int /*<<< orphan*/ **) ; 

isc_result_t
isc_task_create(isc_taskmgr_t *manager, unsigned int quantum,
		isc_task_t **taskp)
{
	REQUIRE(ISCAPI_TASKMGR_VALID(manager));
	REQUIRE(taskp != NULL && *taskp == NULL);

	return (manager->methods->taskcreate(manager, quantum, taskp));
}