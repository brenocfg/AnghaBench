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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {char const* path; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_11__ {int /*<<< orphan*/  distrust_filemode; } ;
typedef  TYPE_3__ git_index ;

/* Variables and functions */
 int git_blob__create_from_paths (int /*<<< orphan*/ *,struct stat*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int git_index_add (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_entry__init_from_stat (TYPE_2__*,struct stat*,int) ; 
 int git_repository_index__weakptr (TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stash_to_index(
	git_repository *repo,
	git_index *index,
	const char *path)
{
	git_index *repo_index;
	git_index_entry entry = {{0}};
	struct stat st;
	int error;

	if (!git_repository_is_bare(repo) &&
	    (error = git_repository_index__weakptr(&repo_index, repo)) < 0)
		return error;

	if ((error = git_blob__create_from_paths(
	    &entry.id, &st, repo, NULL, path, 0, true)) < 0)
		return error;

	git_index_entry__init_from_stat(&entry, &st,
		(repo_index != NULL || !repo_index->distrust_filemode));

	entry.path = path;

	return git_index_add(index, &entry);
}