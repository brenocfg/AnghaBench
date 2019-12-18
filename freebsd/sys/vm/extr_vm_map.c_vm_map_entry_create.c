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
typedef  TYPE_1__* vm_map_t ;
typedef  int /*<<< orphan*/ * vm_map_entry_t ;
struct TYPE_3__ {scalar_t__ system_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  kmapentzone ; 
 int /*<<< orphan*/  mapentzone ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_map_entry_t
vm_map_entry_create(vm_map_t map)
{
	vm_map_entry_t new_entry;

	if (map->system_map)
		new_entry = uma_zalloc(kmapentzone, M_NOWAIT);
	else
		new_entry = uma_zalloc(mapentzone, M_WAITOK);
	if (new_entry == NULL)
		panic("vm_map_entry_create: kernel resources exhausted");
	return (new_entry);
}