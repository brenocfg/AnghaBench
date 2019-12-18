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
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int git_refdb_iterator (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ git_repository_refdb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_reference_iterator_glob_new(
	git_reference_iterator **out, git_repository *repo, const char *glob)
{
	git_refdb *refdb;

	if (git_repository_refdb__weakptr(&refdb, repo) < 0)
		return -1;

	return git_refdb_iterator(out, refdb, glob);
}