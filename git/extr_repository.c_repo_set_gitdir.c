#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct set_gitdir_args {int /*<<< orphan*/  index_file; int /*<<< orphan*/  graft_file; int /*<<< orphan*/  alternate_db; int /*<<< orphan*/  object_dir; int /*<<< orphan*/  commondir; } ;
struct repository {char* gitdir; char* commondir; int /*<<< orphan*/  index_file; int /*<<< orphan*/  graft_file; TYPE_1__* objects; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  next; } ;
struct TYPE_3__ {char* alternate_db; TYPE_2__* odb; int /*<<< orphan*/ * odb_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  expand_base_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* read_gitfile (char const*) ; 
 int /*<<< orphan*/  repo_set_commondir (struct repository*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xcalloc (int,int) ; 
 char* xstrdup (char const*) ; 
 char* xstrdup_or_null (int /*<<< orphan*/ ) ; 

void repo_set_gitdir(struct repository *repo,
		     const char *root,
		     const struct set_gitdir_args *o)
{
	const char *gitfile = read_gitfile(root);
	/*
	 * repo->gitdir is saved because the caller could pass "root"
	 * that also points to repo->gitdir. We want to keep it alive
	 * until after xstrdup(root). Then we can free it.
	 */
	char *old_gitdir = repo->gitdir;

	repo->gitdir = xstrdup(gitfile ? gitfile : root);
	free(old_gitdir);

	repo_set_commondir(repo, o->commondir);

	if (!repo->objects->odb) {
		repo->objects->odb = xcalloc(1, sizeof(*repo->objects->odb));
		repo->objects->odb_tail = &repo->objects->odb->next;
	}
	expand_base_dir(&repo->objects->odb->path, o->object_dir,
			repo->commondir, "objects");

	free(repo->objects->alternate_db);
	repo->objects->alternate_db = xstrdup_or_null(o->alternate_db);
	expand_base_dir(&repo->graft_file, o->graft_file,
			repo->commondir, "info/grafts");
	expand_base_dir(&repo->index_file, o->index_file,
			repo->gitdir, "index");
}