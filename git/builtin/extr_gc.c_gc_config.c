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

/* Variables and functions */
 int /*<<< orphan*/  aggressive_depth ; 
 int /*<<< orphan*/  aggressive_window ; 
 int /*<<< orphan*/  big_pack_threshold ; 
 int /*<<< orphan*/  detach_auto ; 
 int /*<<< orphan*/  gc_auto_pack_limit ; 
 int /*<<< orphan*/  gc_auto_threshold ; 
 scalar_t__ gc_config_is_timestamp_never (char*) ; 
 int /*<<< orphan*/  gc_log_expire ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_config_bool (char*,char const*) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_expiry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_ulong (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_value (char*,char const**) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  max_delta_cache_size ; 
 int pack_refs ; 
 int /*<<< orphan*/  prune_expire ; 
 scalar_t__ prune_reflogs ; 
 int /*<<< orphan*/  prune_worktrees_expire ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void gc_config(void)
{
	const char *value;

	if (!git_config_get_value("gc.packrefs", &value)) {
		if (value && !strcmp(value, "notbare"))
			pack_refs = -1;
		else
			pack_refs = git_config_bool("gc.packrefs", value);
	}

	if (gc_config_is_timestamp_never("gc.reflogexpire") &&
	    gc_config_is_timestamp_never("gc.reflogexpireunreachable"))
		prune_reflogs = 0;

	git_config_get_int("gc.aggressivewindow", &aggressive_window);
	git_config_get_int("gc.aggressivedepth", &aggressive_depth);
	git_config_get_int("gc.auto", &gc_auto_threshold);
	git_config_get_int("gc.autopacklimit", &gc_auto_pack_limit);
	git_config_get_bool("gc.autodetach", &detach_auto);
	git_config_get_expiry("gc.pruneexpire", &prune_expire);
	git_config_get_expiry("gc.worktreepruneexpire", &prune_worktrees_expire);
	git_config_get_expiry("gc.logexpiry", &gc_log_expire);

	git_config_get_ulong("gc.bigpackthreshold", &big_pack_threshold);
	git_config_get_ulong("pack.deltacachesize", &max_delta_cache_size);

	git_config(git_default_config, NULL);
}