#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  scan_lock; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  os_destroy_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  os_destroy_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_cleanup_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_pqi_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_sis_uninit (TYPE_1__*) ; 

void pqisrc_uninit(pqisrc_softstate_t *softs)
{
	DBG_FUNC("IN\n");
	
	pqisrc_pqi_uninit(softs);

	pqisrc_sis_uninit(softs);

	os_destroy_semaphore(&softs->scan_lock);
	
	os_destroy_intr(softs);

	pqisrc_cleanup_devices(softs);

	DBG_FUNC("OUT\n");
}