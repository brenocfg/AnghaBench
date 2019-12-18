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
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_3__ {scalar_t__ mode; int /*<<< orphan*/  ready_priority_tasks; int /*<<< orphan*/  ready_tasks; } ;
typedef  TYPE_1__ isc__taskmgr_t ;
typedef  int /*<<< orphan*/  isc__tasklist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_TF (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_taskmgrmode_normal ; 

__attribute__((used)) static inline isc_boolean_t
empty_readyq(isc__taskmgr_t *manager) {
	isc__tasklist_t queue;

	if (manager->mode == isc_taskmgrmode_normal)
		queue = manager->ready_tasks;
	else
		queue = manager->ready_priority_tasks;

	return (ISC_TF(EMPTY(queue)));
}