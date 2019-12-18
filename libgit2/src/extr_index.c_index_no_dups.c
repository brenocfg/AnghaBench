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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE (TYPE_1__ const*) ; 
 int /*<<< orphan*/  GIT_UNUSED (void**) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int index_no_dups(void **old, void *new)
{
	const git_index_entry *entry = new;
	GIT_UNUSED(old);
	git_error_set(GIT_ERROR_INDEX, "'%s' appears multiple times at stage %d",
		entry->path, GIT_INDEX_ENTRY_STAGE(entry));
	return GIT_EEXISTS;
}