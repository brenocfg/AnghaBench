#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ line_count; } ;
typedef  TYPE_1__ git_patch_hunk ;
struct TYPE_7__ {int /*<<< orphan*/  hunks; } ;
typedef  TYPE_2__ git_patch ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 TYPE_1__* git_array_get (int /*<<< orphan*/ ,size_t) ; 
 int patch_error_outofrange (char*) ; 

int git_patch_num_lines_in_hunk(const git_patch *patch, size_t hunk_idx)
{
	git_patch_hunk *hunk;
	assert(patch);

	if (!(hunk = git_array_get(patch->hunks, hunk_idx)))
		return patch_error_outofrange("hunk");
	return (int)hunk->line_count;
}