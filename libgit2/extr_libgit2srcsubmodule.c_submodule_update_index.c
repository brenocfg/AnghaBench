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
struct TYPE_4__ {int flags; int /*<<< orphan*/  path; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_SUBMODULE_STATUS_IN_INDEX ; 
 int GIT_SUBMODULE_STATUS__INDEX_OID_VALID ; 
 int /*<<< orphan*/ * git_index_get_bypath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submodule_update_from_index_entry (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int submodule_update_index(git_submodule *sm)
{
	git_index *index;
	const git_index_entry *ie;

	if (git_repository_index__weakptr(&index, sm->repo) < 0)
		return -1;

	sm->flags = sm->flags &
		~(GIT_SUBMODULE_STATUS_IN_INDEX |
		  GIT_SUBMODULE_STATUS__INDEX_OID_VALID);

	if (!(ie = git_index_get_bypath(index, sm->path, 0)))
		return 0;

	submodule_update_from_index_entry(sm, ie);

	return 0;
}