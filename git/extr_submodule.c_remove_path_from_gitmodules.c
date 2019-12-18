#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct submodule {char* name; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITMODULES_FILE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_rename_section_in_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_gitmodules_unmerged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct submodule* submodule_from_path (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* the_repository ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

int remove_path_from_gitmodules(const char *path)
{
	struct strbuf sect = STRBUF_INIT;
	const struct submodule *submodule;

	if (!file_exists(GITMODULES_FILE)) /* Do nothing without .gitmodules */
		return -1;

	if (is_gitmodules_unmerged(the_repository->index))
		die(_("Cannot change unmerged .gitmodules, resolve merge conflicts first"));

	submodule = submodule_from_path(the_repository, &null_oid, path);
	if (!submodule || !submodule->name) {
		warning(_("Could not find section in .gitmodules where path=%s"), path);
		return -1;
	}
	strbuf_addstr(&sect, "submodule.");
	strbuf_addstr(&sect, submodule->name);
	if (git_config_rename_section_in_file(GITMODULES_FILE, sect.buf, NULL) < 0) {
		/* Maybe the user already did that, don't error out here */
		warning(_("Could not remove .gitmodules entry for %s"), path);
		strbuf_release(&sect);
		return -1;
	}
	strbuf_release(&sect);
	return 0;
}