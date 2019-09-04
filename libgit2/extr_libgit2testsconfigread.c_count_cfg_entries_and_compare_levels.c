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
struct TYPE_3__ {scalar_t__ level; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;

/* Variables and functions */
 scalar_t__ GIT_CONFIG_LEVEL_GLOBAL ; 
 scalar_t__ GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int count_cfg_entries_and_compare_levels(
	const git_config_entry *entry, void *payload)
{
	int *count = payload;

	if (!strcmp(entry->value, "7") || !strcmp(entry->value, "17"))
		cl_assert(entry->level == GIT_CONFIG_LEVEL_GLOBAL);
	else
		cl_assert(entry->level == GIT_CONFIG_LEVEL_SYSTEM);

	(*count)++;
	return 0;
}