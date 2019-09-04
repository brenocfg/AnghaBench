#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int git_refdb_delete (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_refdb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_reference_remove(git_repository *repo, const char *name)
{
	git_refdb *db;
	int error;

	if ((error = git_repository_refdb__weakptr(&db, repo)) < 0)
		return error;

	return git_refdb_delete(db, name, NULL, NULL);
}