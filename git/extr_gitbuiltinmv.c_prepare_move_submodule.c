#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* SUBMODULE_WITH_GITDIR ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__** active_cache ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  is_staging_gitmodules_ok (int /*<<< orphan*/ *) ; 
 char* read_gitfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_index ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void prepare_move_submodule(const char *src, int first,
				   const char **submodule_gitfile)
{
	struct strbuf submodule_dotgit = STRBUF_INIT;
	if (!S_ISGITLINK(active_cache[first]->ce_mode))
		die(_("Directory %s is in index and no submodule?"), src);
	if (!is_staging_gitmodules_ok(&the_index))
		die(_("Please stage your changes to .gitmodules or stash them to proceed"));
	strbuf_addf(&submodule_dotgit, "%s/.git", src);
	*submodule_gitfile = read_gitfile(submodule_dotgit.buf);
	if (*submodule_gitfile)
		*submodule_gitfile = xstrdup(*submodule_gitfile);
	else
		*submodule_gitfile = SUBMODULE_WITH_GITDIR;
	strbuf_release(&submodule_dotgit);
}