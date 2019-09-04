#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dirty; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int GIT_EINDEXDIRTY ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_index__enforce_unsaved_safety ; 
 int git_index_read (TYPE_1__*,int) ; 

int git_index_read_safely(git_index *index)
{
	if (git_index__enforce_unsaved_safety && index->dirty) {
		git_error_set(GIT_ERROR_INDEX,
			"the index has unsaved changes that would be overwritten by this operation");
		return GIT_EINDEXDIRTY;
	}

	return git_index_read(index, false);
}