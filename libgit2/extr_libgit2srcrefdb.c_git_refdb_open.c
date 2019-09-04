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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_refdb_backend ;
struct TYPE_5__ {int /*<<< orphan*/ * backend; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_refdb_backend_fs (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (TYPE_1__*) ; 
 scalar_t__ git_refdb_new (TYPE_1__**,int /*<<< orphan*/ *) ; 

int git_refdb_open(git_refdb **out, git_repository *repo)
{
	git_refdb *db;
	git_refdb_backend *dir;

	assert(out && repo);

	*out = NULL;

	if (git_refdb_new(&db, repo) < 0)
		return -1;

	/* Add the default (filesystem) backend */
	if (git_refdb_backend_fs(&dir, repo) < 0) {
		git_refdb_free(db);
		return -1;
	}

	db->repo = repo;
	db->backend = dir;

	*out = db;
	return 0;
}