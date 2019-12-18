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
struct string_list {int dummy; } ;
struct notes_rewrite_cfg {char const* cmd; int enabled; int strdup_strings; int refs_from_env; int mode_from_env; struct notes_rewrite_cfg* refs; int /*<<< orphan*/  trees; int /*<<< orphan*/  nr; int /*<<< orphan*/  combine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_NOTES_REWRITE_MODE_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_NOTES_REWRITE_REF_ENVIRONMENT ; 
 int /*<<< orphan*/  NOTES_INIT_WRITABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  combine_notes_concatenate ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (struct notes_rewrite_cfg*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,struct notes_rewrite_cfg*) ; 
 int /*<<< orphan*/  load_notes_trees (struct notes_rewrite_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notes_rewrite_config ; 
 int /*<<< orphan*/  parse_combine_notes_fn (char const*) ; 
 int /*<<< orphan*/  string_list_add_refs_from_colon_sep (struct notes_rewrite_cfg*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct notes_rewrite_cfg*,int /*<<< orphan*/ ) ; 
 struct notes_rewrite_cfg* xcalloc (int,int) ; 
 struct notes_rewrite_cfg* xmalloc (int) ; 

struct notes_rewrite_cfg *init_copy_notes_for_rewrite(const char *cmd)
{
	struct notes_rewrite_cfg *c = xmalloc(sizeof(struct notes_rewrite_cfg));
	const char *rewrite_mode_env = getenv(GIT_NOTES_REWRITE_MODE_ENVIRONMENT);
	const char *rewrite_refs_env = getenv(GIT_NOTES_REWRITE_REF_ENVIRONMENT);
	c->cmd = cmd;
	c->enabled = 1;
	c->combine = combine_notes_concatenate;
	c->refs = xcalloc(1, sizeof(struct string_list));
	c->refs->strdup_strings = 1;
	c->refs_from_env = 0;
	c->mode_from_env = 0;
	if (rewrite_mode_env) {
		c->mode_from_env = 1;
		c->combine = parse_combine_notes_fn(rewrite_mode_env);
		if (!c->combine)
			/*
			 * TRANSLATORS: The first %s is the name of
			 * the environment variable, the second %s is
			 * its value.
			 */
			error(_("Bad %s value: '%s'"), GIT_NOTES_REWRITE_MODE_ENVIRONMENT,
					rewrite_mode_env);
	}
	if (rewrite_refs_env) {
		c->refs_from_env = 1;
		string_list_add_refs_from_colon_sep(c->refs, rewrite_refs_env);
	}
	git_config(notes_rewrite_config, c);
	if (!c->enabled || !c->refs->nr) {
		string_list_clear(c->refs, 0);
		free(c->refs);
		free(c);
		return NULL;
	}
	c->trees = load_notes_trees(c->refs, NOTES_INIT_WRITABLE);
	string_list_clear(c->refs, 0);
	free(c->refs);
	return c;
}