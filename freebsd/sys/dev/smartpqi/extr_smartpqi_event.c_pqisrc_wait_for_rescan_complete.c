#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  scan_lock; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_sema_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_sema_unlock (int /*<<< orphan*/ *) ; 

void pqisrc_wait_for_rescan_complete(pqisrc_softstate_t *softs)
{
	os_sema_lock(&softs->scan_lock);
	os_sema_unlock(&softs->scan_lock);
}