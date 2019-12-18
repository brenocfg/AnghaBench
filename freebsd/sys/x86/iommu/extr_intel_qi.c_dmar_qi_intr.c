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
struct dmar_unit {int /*<<< orphan*/  qi_task; int /*<<< orphan*/  qi_taskqueue; int /*<<< orphan*/  unit; int /*<<< orphan*/  qi_enabled; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dmar_qi_intr(void *arg)
{
	struct dmar_unit *unit;

	unit = arg;
	KASSERT(unit->qi_enabled, ("dmar%d: QI is not enabled", unit->unit));
	taskqueue_enqueue(unit->qi_taskqueue, &unit->qi_task);
	return (FILTER_HANDLED);
}