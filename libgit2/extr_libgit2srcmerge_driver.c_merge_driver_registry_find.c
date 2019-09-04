#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  drivers; } ;

/* Variables and functions */
 int git_vector_search2 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  merge_driver_entry_search ; 
 TYPE_1__ merge_driver_registry ; 

__attribute__((used)) static int merge_driver_registry_find(size_t *pos, const char *name)
{
	return git_vector_search2(pos, &merge_driver_registry.drivers,
		merge_driver_entry_search, name);
}