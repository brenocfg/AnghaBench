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
 int config_set_in_gitmodules_file_gently (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ is_gitmodules_unmerged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct submodule* submodule_from_path (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* the_repository ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

int update_path_in_gitmodules(const char *oldpath, const char *newpath)
{
	struct strbuf entry = STRBUF_INIT;
	const struct submodule *submodule;
	int ret;

	if (!file_exists(GITMODULES_FILE)) /* Do nothing without .gitmodules */
		return -1;

	if (is_gitmodules_unmerged(the_repository->index))
		die(_("Cannot change unmerged .gitmodules, resolve merge conflicts first"));

	submodule = submodule_from_path(the_repository, &null_oid, oldpath);
	if (!submodule || !submodule->name) {
		warning(_("Could not find section in .gitmodules where path=%s"), oldpath);
		return -1;
	}
	strbuf_addstr(&entry, "submodule.");
	strbuf_addstr(&entry, submodule->name);
	strbuf_addstr(&entry, ".path");
	ret = config_set_in_gitmodules_file_gently(entry.buf, newpath);
	strbuf_release(&entry);
	return ret;
}