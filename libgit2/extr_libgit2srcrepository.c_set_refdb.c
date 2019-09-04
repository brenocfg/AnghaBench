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
struct TYPE_4__ {int /*<<< orphan*/  _refdb; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_OWN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * git__swap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_refdb(git_repository *repo, git_refdb *refdb)
{
	if (refdb) {
		GIT_REFCOUNT_OWN(refdb, repo);
		GIT_REFCOUNT_INC(refdb);
	}

	if ((refdb = git__swap(repo->_refdb, refdb)) != NULL) {
		GIT_REFCOUNT_OWN(refdb, NULL);
		git_refdb_free(refdb);
	}
}