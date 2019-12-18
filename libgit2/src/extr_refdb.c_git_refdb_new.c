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
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__calloc (int,int) ; 

int git_refdb_new(git_refdb **out, git_repository *repo)
{
	git_refdb *db;

	assert(out && repo);

	db = git__calloc(1, sizeof(*db));
	GIT_ERROR_CHECK_ALLOC(db);

	db->repo = repo;

	*out = db;
	GIT_REFCOUNT_INC(db);
	return 0;
}