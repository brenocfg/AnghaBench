#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_4__ {void* start; void* end; int /*<<< orphan*/  eflags; struct TYPE_4__* prev; struct TYPE_4__* next; } ;
struct TYPE_5__ {scalar_t__ nupdates; scalar_t__ anon_loc; scalar_t__ busy; scalar_t__ timestamp; int /*<<< orphan*/ * root; scalar_t__ flags; TYPE_1__ header; int /*<<< orphan*/  pmap; scalar_t__ system_map; int /*<<< orphan*/  needs_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAP_ENTRY_HEADER ; 

__attribute__((used)) static void
_vm_map_init(vm_map_t map, pmap_t pmap, vm_offset_t min, vm_offset_t max)
{

	map->header.next = map->header.prev = &map->header;
	map->header.eflags = MAP_ENTRY_HEADER;
	map->needs_wakeup = FALSE;
	map->system_map = 0;
	map->pmap = pmap;
	map->header.end = min;
	map->header.start = max;
	map->flags = 0;
	map->root = NULL;
	map->timestamp = 0;
	map->busy = 0;
	map->anon_loc = 0;
#ifdef DIAGNOSTIC
	map->nupdates = 0;
#endif
}