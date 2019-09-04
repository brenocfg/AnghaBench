#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_5__ {int strategy; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ checkout_data ;

/* Variables and functions */
 int GIT_CHECKOUT_DONT_UPDATE_INDEX ; 
 int /*<<< orphan*/  checkout_conflict_append_remove ; 
 int checkout_conflicts_foreach (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int checkout_get_remove_conflicts(
	checkout_data *data,
	git_iterator *workdir,
	git_vector *pathspec)
{
	if ((data->strategy & GIT_CHECKOUT_DONT_UPDATE_INDEX) != 0)
		return 0;

	return checkout_conflicts_foreach(data, data->index, workdir, pathspec, checkout_conflict_append_remove, data);
}