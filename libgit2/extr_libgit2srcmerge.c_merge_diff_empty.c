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
struct TYPE_4__ {TYPE_2__** contents; } ;
typedef  TYPE_1__ git_vector ;
struct TYPE_5__ {int /*<<< orphan*/  their_entry; int /*<<< orphan*/  our_entry; int /*<<< orphan*/  ancestor_entry; } ;
typedef  TYPE_2__ git_merge_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MERGE_INDEX_ENTRY_EXISTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int merge_diff_empty(const git_vector *conflicts, size_t idx, void *p)
{
	git_merge_diff *conflict = conflicts->contents[idx];

	GIT_UNUSED(p);

	return (!GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->ancestor_entry) &&
		!GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->our_entry) &&
		!GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->their_entry));
}