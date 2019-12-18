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
struct submodule {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_super_prefix_or_empty () ; 
 char* git_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 scalar_t__ read_gitfile (char*) ; 
 char* real_pathdup (char const*,int) ; 
 int /*<<< orphan*/  relocate_gitdir (char const*,char*,char*) ; 
 scalar_t__ safe_create_leading_directories_const (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ submodule_uses_worktrees (char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static void relocate_single_git_dir_into_superproject(const char *path)
{
	char *old_git_dir = NULL, *real_old_git_dir = NULL, *real_new_git_dir = NULL;
	const char *new_git_dir;
	const struct submodule *sub;

	if (submodule_uses_worktrees(path))
		die(_("relocate_gitdir for submodule '%s' with "
		      "more than one worktree not supported"), path);

	old_git_dir = xstrfmt("%s/.git", path);
	if (read_gitfile(old_git_dir))
		/* If it is an actual gitfile, it doesn't need migration. */
		return;

	real_old_git_dir = real_pathdup(old_git_dir, 1);

	sub = submodule_from_path(the_repository, &null_oid, path);
	if (!sub)
		die(_("could not lookup name for submodule '%s'"), path);

	new_git_dir = git_path("modules/%s", sub->name);
	if (safe_create_leading_directories_const(new_git_dir) < 0)
		die(_("could not create directory '%s'"), new_git_dir);
	real_new_git_dir = real_pathdup(new_git_dir, 1);

	fprintf(stderr, _("Migrating git directory of '%s%s' from\n'%s' to\n'%s'\n"),
		get_super_prefix_or_empty(), path,
		real_old_git_dir, real_new_git_dir);

	relocate_gitdir(path, real_old_git_dir, real_new_git_dir);

	free(old_git_dir);
	free(real_old_git_dir);
	free(real_new_git_dir);
}