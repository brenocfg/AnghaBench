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
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;
typedef  int /*<<< orphan*/  isc__task_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_SHUTTINGDOWN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALID_TASK (int /*<<< orphan*/ *) ; 

isc_boolean_t
isc_task_exiting(isc_task_t *t) {
	isc__task_t *task = (isc__task_t *)t;

	REQUIRE(VALID_TASK(task));
	return (TASK_SHUTTINGDOWN(task));
}