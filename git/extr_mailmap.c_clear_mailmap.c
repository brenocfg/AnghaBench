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
struct string_list {int strdup_strings; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_mm (char*,...) ; 
 int /*<<< orphan*/  free_mailmap_entry ; 
 int /*<<< orphan*/  string_list_clear_func (struct string_list*,int /*<<< orphan*/ ) ; 

void clear_mailmap(struct string_list *map)
{
	debug_mm("mailmap: clearing %d entries...\n", map->nr);
	map->strdup_strings = 1;
	string_list_clear_func(map, free_mailmap_entry);
	debug_mm("mailmap: cleared\n");
}