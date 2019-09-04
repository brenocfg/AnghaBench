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
struct submodule {int recommend_shallow; void* branch; int /*<<< orphan*/  name; TYPE_1__ update_strategy; void* url; void* ignore; int /*<<< orphan*/  fetch_recurse; void* path; } ;
struct strbuf {char const* buf; } ;
struct parse_config_parameter {int /*<<< orphan*/  treeish_name; int /*<<< orphan*/  overwrite; int /*<<< orphan*/  gitmodules_oid; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECURSE_SUBMODULES_NONE ; 
 scalar_t__ SM_UPDATE_UNSPECIFIED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cache_put_path (int /*<<< orphan*/ ,struct submodule*) ; 
 int /*<<< orphan*/  cache_remove_path (int /*<<< orphan*/ ,struct submodule*) ; 
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int git_config_bool (char const*,char const*) ; 
 int is_null_oid (int /*<<< orphan*/ ) ; 
 scalar_t__ looks_like_command_line_option (char const*) ; 
 struct submodule* lookup_or_create_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  name_and_item_from_var (char const*,struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  parse_fetch_recurse (char const*,char const*,int) ; 
 scalar_t__ parse_submodule_update_strategy (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warn_command_line_option (char const*,char const*) ; 
 int /*<<< orphan*/  warn_multiple_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warning (char*,char const*,char const*) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static int parse_config(const char *var, const char *value, void *data)
{
	struct parse_config_parameter *me = data;
	struct submodule *submodule;
	struct strbuf name = STRBUF_INIT, item = STRBUF_INIT;
	int ret = 0;

	/* this also ensures that we only parse submodule entries */
	if (!name_and_item_from_var(var, &name, &item))
		return 0;

	submodule = lookup_or_create_by_name(me->cache,
					     me->gitmodules_oid,
					     name.buf);

	if (!strcmp(item.buf, "path")) {
		if (!value)
			ret = config_error_nonbool(var);
		else if (looks_like_command_line_option(value))
			warn_command_line_option(var, value);
		else if (!me->overwrite && submodule->path)
			warn_multiple_config(me->treeish_name, submodule->name,
					"path");
		else {
			if (submodule->path)
				cache_remove_path(me->cache, submodule);
			free((void *) submodule->path);
			submodule->path = xstrdup(value);
			cache_put_path(me->cache, submodule);
		}
	} else if (!strcmp(item.buf, "fetchrecursesubmodules")) {
		/* when parsing worktree configurations we can die early */
		int die_on_error = is_null_oid(me->gitmodules_oid);
		if (!me->overwrite &&
		    submodule->fetch_recurse != RECURSE_SUBMODULES_NONE)
			warn_multiple_config(me->treeish_name, submodule->name,
					"fetchrecursesubmodules");
		else
			submodule->fetch_recurse = parse_fetch_recurse(
								var, value,
								die_on_error);
	} else if (!strcmp(item.buf, "ignore")) {
		if (!value)
			ret = config_error_nonbool(var);
		else if (!me->overwrite && submodule->ignore)
			warn_multiple_config(me->treeish_name, submodule->name,
					"ignore");
		else if (strcmp(value, "untracked") &&
			 strcmp(value, "dirty") &&
			 strcmp(value, "all") &&
			 strcmp(value, "none"))
			warning("Invalid parameter '%s' for config option "
					"'submodule.%s.ignore'", value, name.buf);
		else {
			free((void *) submodule->ignore);
			submodule->ignore = xstrdup(value);
		}
	} else if (!strcmp(item.buf, "url")) {
		if (!value) {
			ret = config_error_nonbool(var);
		} else if (looks_like_command_line_option(value)) {
			warn_command_line_option(var, value);
		} else if (!me->overwrite && submodule->url) {
			warn_multiple_config(me->treeish_name, submodule->name,
					"url");
		} else {
			free((void *) submodule->url);
			submodule->url = xstrdup(value);
		}
	} else if (!strcmp(item.buf, "update")) {
		if (!value)
			ret = config_error_nonbool(var);
		else if (!me->overwrite &&
			 submodule->update_strategy.type != SM_UPDATE_UNSPECIFIED)
			warn_multiple_config(me->treeish_name, submodule->name,
					     "update");
		else if (parse_submodule_update_strategy(value,
			 &submodule->update_strategy) < 0)
				die(_("invalid value for %s"), var);
	} else if (!strcmp(item.buf, "shallow")) {
		if (!me->overwrite && submodule->recommend_shallow != -1)
			warn_multiple_config(me->treeish_name, submodule->name,
					     "shallow");
		else
			submodule->recommend_shallow =
				git_config_bool(var, value);
	} else if (!strcmp(item.buf, "branch")) {
		if (!me->overwrite && submodule->branch)
			warn_multiple_config(me->treeish_name, submodule->name,
					     "branch");
		else {
			free((void *)submodule->branch);
			submodule->branch = xstrdup(value);
		}
	}

	strbuf_release(&name);
	strbuf_release(&item);

	return ret;
}