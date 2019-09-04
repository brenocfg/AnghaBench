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
struct TYPE_2__ {scalar_t__ type; } ;
struct submodule {char* name; char* url; TYPE_1__ update_strategy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 unsigned int OPT_QUIET ; 
 scalar_t__ SM_UPDATE_COMMAND ; 
 scalar_t__ SM_UPDATE_UNSPECIFIED ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 char* compute_submodule_clone_url (char*) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_submodule_displaypath (char const*,char const*) ; 
 scalar_t__ git_config_get_string (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ git_config_set_gently (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_submodule_active (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  null_oid ; 
 scalar_t__ starts_with_dot_dot_slash (char*) ; 
 scalar_t__ starts_with_dot_slash (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 char* submodule_strategy_to_string (TYPE_1__*) ; 
 int /*<<< orphan*/  the_repository ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void init_submodule(const char *path, const char *prefix,
			   unsigned int flags)
{
	const struct submodule *sub;
	struct strbuf sb = STRBUF_INIT;
	char *upd = NULL, *url = NULL, *displaypath;

	displaypath = get_submodule_displaypath(path, prefix);

	sub = submodule_from_path(the_repository, &null_oid, path);

	if (!sub)
		die(_("No url found for submodule path '%s' in .gitmodules"),
			displaypath);

	/*
	 * NEEDSWORK: In a multi-working-tree world, this needs to be
	 * set in the per-worktree config.
	 *
	 * Set active flag for the submodule being initialized
	 */
	if (!is_submodule_active(the_repository, path)) {
		strbuf_addf(&sb, "submodule.%s.active", sub->name);
		git_config_set_gently(sb.buf, "true");
		strbuf_reset(&sb);
	}

	/*
	 * Copy url setting when it is not set yet.
	 * To look up the url in .git/config, we must not fall back to
	 * .gitmodules, so look it up directly.
	 */
	strbuf_addf(&sb, "submodule.%s.url", sub->name);
	if (git_config_get_string(sb.buf, &url)) {
		if (!sub->url)
			die(_("No url found for submodule path '%s' in .gitmodules"),
				displaypath);

		url = xstrdup(sub->url);

		/* Possibly a url relative to parent */
		if (starts_with_dot_dot_slash(url) ||
		    starts_with_dot_slash(url)) {
			char *oldurl = url;
			url = compute_submodule_clone_url(oldurl);
			free(oldurl);
		}

		if (git_config_set_gently(sb.buf, url))
			die(_("Failed to register url for submodule path '%s'"),
			    displaypath);
		if (!(flags & OPT_QUIET))
			fprintf(stderr,
				_("Submodule '%s' (%s) registered for path '%s'\n"),
				sub->name, url, displaypath);
	}
	strbuf_reset(&sb);

	/* Copy "update" setting when it is not set yet */
	strbuf_addf(&sb, "submodule.%s.update", sub->name);
	if (git_config_get_string(sb.buf, &upd) &&
	    sub->update_strategy.type != SM_UPDATE_UNSPECIFIED) {
		if (sub->update_strategy.type == SM_UPDATE_COMMAND) {
			fprintf(stderr, _("warning: command update mode suggested for submodule '%s'\n"),
				sub->name);
			upd = xstrdup("none");
		} else
			upd = xstrdup(submodule_strategy_to_string(&sub->update_strategy));

		if (git_config_set_gently(sb.buf, upd))
			die(_("Failed to register update mode for submodule path '%s'"), displaypath);
	}
	strbuf_release(&sb);
	free(displaypath);
	free(url);
	free(upd);
}