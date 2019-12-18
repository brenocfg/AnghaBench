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
struct submodule {char const* name; char* branch; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  null_oid ; 
 scalar_t__ repo_config_get_string_const (int /*<<< orphan*/ ,char*,char const**) ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static const char *remote_submodule_branch(const char *path)
{
	const struct submodule *sub;
	const char *branch = NULL;
	char *key;

	sub = submodule_from_path(the_repository, &null_oid, path);
	if (!sub)
		return NULL;

	key = xstrfmt("submodule.%s.branch", sub->name);
	if (repo_config_get_string_const(the_repository, key, &branch))
		branch = sub->branch;
	free(key);

	if (!branch)
		return "master";

	if (!strcmp(branch, ".")) {
		const char *refname = resolve_ref_unsafe("HEAD", 0, NULL, NULL);

		if (!refname)
			die(_("No such ref: %s"), "HEAD");

		/* detached HEAD */
		if (!strcmp(refname, "HEAD"))
			die(_("Submodule (%s) branch configured to inherit "
			      "branch from superproject, but the superproject "
			      "is not on any branch"), sub->name);

		if (!skip_prefix(refname, "refs/heads/", &refname))
			die(_("Expecting a full ref name, got %s"), refname);
		return refname;
	}

	return branch;
}