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
struct commit_name {unsigned int prio; int /*<<< orphan*/  peeled; int /*<<< orphan*/ * path; int /*<<< orphan*/  sha1; scalar_t__ name_checked; int /*<<< orphan*/ * tag; } ;
typedef  int /*<<< orphan*/  git_tag ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oidmap ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct commit_name*) ; 
 struct commit_name* find_commit_name (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 struct commit_name* git__malloc (int) ; 
 int /*<<< orphan*/ * git__strdup (char const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ git_oidmap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct commit_name*) ; 
 int /*<<< orphan*/  git_tag_free (int /*<<< orphan*/ *) ; 
 scalar_t__ replace_name (int /*<<< orphan*/ **,int /*<<< orphan*/ *,struct commit_name*,unsigned int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int add_to_known_names(
	git_repository *repo,
	git_oidmap *names,
	const char *path,
	const git_oid *peeled,
	unsigned int prio,
	const git_oid *sha1)
{
	struct commit_name *e = find_commit_name(names, peeled);
	bool found = (e != NULL);

	git_tag *tag = NULL;
	if (replace_name(&tag, repo, e, prio, sha1)) {
		if (!found) {
			e = git__malloc(sizeof(struct commit_name));
			GIT_ERROR_CHECK_ALLOC(e);

			e->path = NULL;
			e->tag = NULL;
		}

		if (e->tag)
			git_tag_free(e->tag);
		e->tag = tag;
		e->prio = prio;
		e->name_checked = 0;
		git_oid_cpy(&e->sha1, sha1);
		git__free(e->path);
		e->path = git__strdup(path);
		git_oid_cpy(&e->peeled, peeled);

		if (!found && git_oidmap_set(names, &e->peeled, e) < 0)
			return -1;
	}
	else
		git_tag_free(tag);

	return 0;
}