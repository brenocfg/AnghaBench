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
typedef  int /*<<< orphan*/  isc_taskmgr_t ;
typedef  int isc_boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ isc__taskmgr_t ;

/* Variables and functions */
 int ISC_FALSE ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  empty_readyq (TYPE_1__*) ; 
 TYPE_1__* taskmgr ; 

isc_boolean_t
isc__taskmgr_ready(isc_taskmgr_t *manager0) {
	isc__taskmgr_t *manager = (void*)manager0;
	isc_boolean_t is_ready;

#ifdef USE_SHARED_MANAGER
	if (manager == NULL)
		manager = taskmgr;
#endif
	if (manager == NULL)
		return (ISC_FALSE);

	LOCK(&manager->lock);
	is_ready = !empty_readyq(manager);
	UNLOCK(&manager->lock);

	return (is_ready);
}