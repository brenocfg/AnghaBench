#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_6__ {int strategy; } ;
typedef  TYPE_1__ checkout_data ;

/* Variables and functions */
 int GIT_CHECKOUT_SKIP_UNMERGED ; 
 int checkout_conflicts_coalesce_renames (TYPE_1__*) ; 
 int checkout_conflicts_load (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int checkout_conflicts_mark_directoryfile (TYPE_1__*) ; 

__attribute__((used)) static int checkout_get_update_conflicts(
	checkout_data *data,
	git_iterator *workdir,
	git_vector *pathspec)
{
	int error = 0;

	if (data->strategy & GIT_CHECKOUT_SKIP_UNMERGED)
		return 0;

	if ((error = checkout_conflicts_load(data, workdir, pathspec)) < 0 ||
		(error = checkout_conflicts_coalesce_renames(data)) < 0 ||
		(error = checkout_conflicts_mark_directoryfile(data)) < 0)
		goto done;

done:
	return error;
}