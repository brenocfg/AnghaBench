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
struct notes_rewrite_cfg {char* cmd; int /*<<< orphan*/  refs; int /*<<< orphan*/  refs_from_env; int /*<<< orphan*/  combine; int /*<<< orphan*/  mode_from_env; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  parse_combine_notes_fn (char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_add_refs_by_glob (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int notes_rewrite_config(const char *k, const char *v, void *cb)
{
	struct notes_rewrite_cfg *c = cb;
	if (starts_with(k, "notes.rewrite.") && !strcmp(k+14, c->cmd)) {
		c->enabled = git_config_bool(k, v);
		return 0;
	} else if (!c->mode_from_env && !strcmp(k, "notes.rewritemode")) {
		if (!v)
			return config_error_nonbool(k);
		c->combine = parse_combine_notes_fn(v);
		if (!c->combine) {
			error(_("Bad notes.rewriteMode value: '%s'"), v);
			return 1;
		}
		return 0;
	} else if (!c->refs_from_env && !strcmp(k, "notes.rewriteref")) {
		/* note that a refs/ prefix is implied in the
		 * underlying for_each_glob_ref */
		if (starts_with(v, "refs/notes/"))
			string_list_add_refs_by_glob(c->refs, v);
		else
			warning(_("Refusing to rewrite notes in %s"
				" (outside of refs/notes/)"), v);
		return 0;
	}

	return 0;
}