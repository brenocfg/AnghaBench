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
struct TYPE_5__ {int flags; int /*<<< orphan*/  const wd_oid; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_SUBMODULE_STATUS__WD_OID_VALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_open_bare (int /*<<< orphan*/ **,TYPE_1__*) ; 

const git_oid *git_submodule_wd_id(git_submodule *submodule)
{
	assert(submodule);

	/* load unless we think we have a valid oid */
	if (!(submodule->flags & GIT_SUBMODULE_STATUS__WD_OID_VALID)) {
		git_repository *subrepo;

		/* calling submodule open grabs the HEAD OID if possible */
		if (!git_submodule_open_bare(&subrepo, submodule))
			git_repository_free(subrepo);
		else
			git_error_clear();
	}

	if (submodule->flags & GIT_SUBMODULE_STATUS__WD_OID_VALID)
		return &submodule->wd_oid;
	else
		return NULL;
}