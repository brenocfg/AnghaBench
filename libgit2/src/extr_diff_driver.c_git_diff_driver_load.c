#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_22__ {int /*<<< orphan*/  drivers; } ;
typedef  TYPE_1__ git_diff_driver_registry ;
struct TYPE_23__ {int /*<<< orphan*/  name; int /*<<< orphan*/  word_pattern; int /*<<< orphan*/  type; int /*<<< orphan*/  fn_patterns; int /*<<< orphan*/  binary_flags; } ;
typedef  TYPE_2__ git_diff_driver ;
struct TYPE_24__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_25__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_DRIVER_AUTO ; 
 size_t DIFF_DRIVER_BINARY ; 
 int /*<<< orphan*/  DIFF_DRIVER_PATTERNLIST ; 
 TYPE_4__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FORCE_TEXT ; 
 int GIT_ENOTFOUND ; 
 int diff_driver_alloc (TYPE_2__**,size_t*,char const*) ; 
 int /*<<< orphan*/  diff_driver_funcname ; 
 int /*<<< orphan*/  diff_driver_xfuncname ; 
 scalar_t__ git_array_size (int /*<<< orphan*/ ) ; 
 int git_buf_PUTS (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_4__*) ; 
 int git_buf_printf (TYPE_4__*,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_4__*,scalar_t__) ; 
 int git_config__get_bool_force (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int git_config__lookup_entry (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_multivar_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int git_diff_driver_builtin (TYPE_2__**,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_diff_driver_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_regexp_compile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_1__* git_repository_driver_registry (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_strmap_get (int /*<<< orphan*/ ,char const*) ; 
 int git_strmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* global_drivers ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int git_diff_driver_load(
	git_diff_driver **out, git_repository *repo, const char *driver_name)
{
	int error = 0;
	git_diff_driver_registry *reg;
	git_diff_driver *drv;
	size_t namelen;
	git_config *cfg = NULL;
	git_buf name = GIT_BUF_INIT;
	git_config_entry *ce = NULL;
	bool found_driver = false;

	if ((reg = git_repository_driver_registry(repo)) == NULL)
		return -1;

	if ((drv = git_strmap_get(reg->drivers, driver_name)) != NULL) {
		*out = drv;
		return 0;
	}

	if ((error = diff_driver_alloc(&drv, &namelen, driver_name)) < 0)
		goto done;

	drv->type = DIFF_DRIVER_AUTO;

	/* if you can't read config for repo, just use default driver */
	if (git_repository_config_snapshot(&cfg, repo) < 0) {
		git_error_clear();
		goto done;
	}

	if ((error = git_buf_printf(&name, "diff.%s.binary", driver_name)) < 0)
		goto done;

	switch (git_config__get_bool_force(cfg, name.ptr, -1)) {
	case true:
		/* if diff.<driver>.binary is true, just return the binary driver */
		*out = &global_drivers[DIFF_DRIVER_BINARY];
		goto done;
	case false:
		/* if diff.<driver>.binary is false, force binary checks off */
		/* but still may have custom function context patterns, etc. */
		drv->binary_flags = GIT_DIFF_FORCE_TEXT;
		found_driver = true;
		break;
	default:
		/* diff.<driver>.binary unspecified or "auto", so just continue */
		break;
	}

	/* TODO: warn if diff.<name>.command or diff.<name>.textconv are set */

	git_buf_truncate(&name, namelen + strlen("diff.."));
	if ((error = git_buf_PUTS(&name, "xfuncname")) < 0)
		goto done;

	if ((error = git_config_get_multivar_foreach(
			cfg, name.ptr, NULL, diff_driver_xfuncname, drv)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto done;
		git_error_clear(); /* no diff.<driver>.xfuncname, so just continue */
	}

	git_buf_truncate(&name, namelen + strlen("diff.."));
	if ((error = git_buf_PUTS(&name, "funcname")) < 0)
		goto done;

	if ((error = git_config_get_multivar_foreach(
			cfg, name.ptr, NULL, diff_driver_funcname, drv)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto done;
		git_error_clear(); /* no diff.<driver>.funcname, so just continue */
	}

	/* if we found any patterns, set driver type to use correct callback */
	if (git_array_size(drv->fn_patterns) > 0) {
		drv->type = DIFF_DRIVER_PATTERNLIST;
		found_driver = true;
	}

	git_buf_truncate(&name, namelen + strlen("diff.."));
	if ((error = git_buf_PUTS(&name, "wordregex")) < 0)
		goto done;

	if ((error = git_config__lookup_entry(&ce, cfg, name.ptr, false)) < 0)
		goto done;
	if (!ce || !ce->value)
		/* no diff.<driver>.wordregex, so just continue */;
	else if (!(error = git_regexp_compile(&drv->word_pattern, ce->value, 0)))
		found_driver = true;
	else {
		/* TODO: warn about bad regex instead of failure */
		goto done;
	}

	/* TODO: look up diff.<driver>.algorithm to turn on minimal / patience
	 * diff in drv->other_flags
	 */

	/* if no driver config found at all, fall back on AUTO driver */
	if (!found_driver)
		goto done;

	/* store driver in registry */
	if ((error = git_strmap_set(reg->drivers, drv->name, drv)) < 0)
		goto done;

	*out = drv;

done:
	git_config_entry_free(ce);
	git_buf_dispose(&name);
	git_config_free(cfg);

	if (!*out) {
		int error2 = git_diff_driver_builtin(out, reg, driver_name);
		if (!error)
			error = error2;
	}

	if (drv && drv != *out)
		git_diff_driver_free(drv);

	return error;
}