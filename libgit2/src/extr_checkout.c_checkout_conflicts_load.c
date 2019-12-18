#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_10__ {int /*<<< orphan*/  names; int /*<<< orphan*/  reuc; } ;
typedef  TYPE_2__ git_index ;
struct TYPE_9__ {int /*<<< orphan*/  _cmp; } ;
struct TYPE_11__ {int /*<<< orphan*/ * update_names; int /*<<< orphan*/ * update_reuc; TYPE_1__ update_conflicts; int /*<<< orphan*/  target; } ;
typedef  TYPE_3__ checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  checkout_conflict_append_update ; 
 int /*<<< orphan*/  checkout_conflictdata_cmp ; 
 scalar_t__ checkout_conflicts_foreach (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* git_iterator_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_conflicts_load(checkout_data *data, git_iterator *workdir, git_vector *pathspec)
{
	git_index *index;

	/* Only write conficts from sources that have them: indexes. */
	if ((index = git_iterator_index(data->target)) == NULL)
		return 0;

	data->update_conflicts._cmp = checkout_conflictdata_cmp;

	if (checkout_conflicts_foreach(data, index, workdir, pathspec, checkout_conflict_append_update, data) < 0)
		return -1;

	/* Collect the REUC and NAME entries */
	data->update_reuc = &index->reuc;
	data->update_names = &index->names;

	return 0;
}