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
struct dmar_unit {int /*<<< orphan*/  dmamap_load_task; int /*<<< orphan*/  delayed_taskqueue; int /*<<< orphan*/  delayed_maps; } ;
struct bus_dmamap_dmar {int locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bus_dmamap_dmar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay_link ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmar_bus_schedule_dmamap(struct dmar_unit *unit, struct bus_dmamap_dmar *map)
{

	map->locked = false;
	DMAR_LOCK(unit);
	TAILQ_INSERT_TAIL(&unit->delayed_maps, map, delay_link);
	DMAR_UNLOCK(unit);
	taskqueue_enqueue(unit->delayed_taskqueue, &unit->dmamap_load_task);
}