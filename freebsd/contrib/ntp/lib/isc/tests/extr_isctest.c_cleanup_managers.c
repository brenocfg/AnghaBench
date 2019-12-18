#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  isc_socketmgr_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_taskmgr_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_timermgr_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * socketmgr ; 
 int /*<<< orphan*/ * taskmgr ; 
 int /*<<< orphan*/ * timermgr ; 

__attribute__((used)) static void
cleanup_managers() {
	if (socketmgr != NULL)
		isc_socketmgr_destroy(&socketmgr);
	if (taskmgr != NULL)
		isc_taskmgr_destroy(&taskmgr);
	if (timermgr != NULL)
		isc_timermgr_destroy(&timermgr);
}