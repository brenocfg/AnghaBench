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
typedef  int /*<<< orphan*/  git_merge_driver_entry ;
struct TYPE_2__ {int /*<<< orphan*/  drivers; } ;

/* Variables and functions */
 int /*<<< orphan*/ * git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__ merge_driver_registry ; 
 int /*<<< orphan*/  merge_driver_registry_find (size_t*,char const*) ; 

__attribute__((used)) static git_merge_driver_entry *merge_driver_registry_lookup(
	size_t *pos, const char *name)
{
	git_merge_driver_entry *entry = NULL;

	if (!merge_driver_registry_find(pos, name))
		entry = git_vector_get(&merge_driver_registry.drivers, *pos);

	return entry;
}