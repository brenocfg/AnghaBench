#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  devlist_lock; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
struct TYPE_10__ {int /*<<< orphan*/  target; } ;
typedef  TYPE_2__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  OS_ACQUIRE_SPINLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_RELEASE_SPINLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_device_mem_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pqisrc_free_tid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqisrc_is_logical_device (TYPE_2__*) ; 

void pqisrc_free_device(pqisrc_softstate_t * softs,pqi_scsi_dev_t *device)
{

		OS_ACQUIRE_SPINLOCK(&softs->devlist_lock);
		if (!pqisrc_is_logical_device(device)) {
			pqisrc_free_tid(softs,device->target);
		}
		pqisrc_device_mem_free(softs, device);
		OS_RELEASE_SPINLOCK(&softs->devlist_lock);

}