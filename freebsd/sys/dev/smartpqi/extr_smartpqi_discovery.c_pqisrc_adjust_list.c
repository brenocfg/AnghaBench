#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  devlist_lock; int /*<<< orphan*/ *** device_list; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
struct TYPE_9__ {size_t target; size_t lun; } ;
typedef  TYPE_2__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  OS_ACQUIRE_SPINLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_RELEASE_SPINLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_device_mem_free (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void pqisrc_adjust_list(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device)
{
	DBG_FUNC("IN\n");

	if (!device) {
		DBG_ERR("softs = %p: device is NULL !!!\n", softs);
		return;
	}

	OS_ACQUIRE_SPINLOCK(&softs->devlist_lock);
	softs->device_list[device->target][device->lun] = NULL;
	OS_RELEASE_SPINLOCK(&softs->devlist_lock);
	pqisrc_device_mem_free(softs, device);

	DBG_FUNC("OUT\n");
}