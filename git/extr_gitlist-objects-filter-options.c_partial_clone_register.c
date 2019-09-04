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
struct list_objects_filter_options {char const* filter_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char const* core_partial_clone_filter_default ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set (char*,char const*) ; 
 scalar_t__* repository_format_partial_clone ; 
 scalar_t__ strcmp (char const*,scalar_t__*) ; 
 void* xstrdup (char const*) ; 

void partial_clone_register(
	const char *remote,
	const struct list_objects_filter_options *filter_options)
{
	/*
	 * Record the name of the partial clone remote in the
	 * config and in the global variable -- the latter is
	 * used throughout to indicate that partial clone is
	 * enabled and to expect missing objects.
	 */
	if (repository_format_partial_clone &&
	    *repository_format_partial_clone &&
	    strcmp(remote, repository_format_partial_clone))
		die(_("cannot change partial clone promisor remote"));

	git_config_set("core.repositoryformatversion", "1");
	git_config_set("extensions.partialclone", remote);

	repository_format_partial_clone = xstrdup(remote);

	/*
	 * Record the initial filter-spec in the config as
	 * the default for subsequent fetches from this remote.
	 */
	core_partial_clone_filter_default =
		xstrdup(filter_options->filter_spec);
	git_config_set("core.partialclonefilter",
		       core_partial_clone_filter_default);
}