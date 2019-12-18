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
struct list_objects_filter_options {int dummy; } ;

/* Variables and functions */
 char* expand_list_objects_filter_spec (struct list_objects_filter_options*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_set (char*,char*) ; 
 int /*<<< orphan*/  promisor_remote_find (char const*) ; 
 int /*<<< orphan*/  promisor_remote_reinit () ; 
 char* xstrfmt (char*,char const*) ; 

void partial_clone_register(
	const char *remote,
	struct list_objects_filter_options *filter_options)
{
	char *cfg_name;
	char *filter_name;

	/* Check if it is already registered */
	if (!promisor_remote_find(remote)) {
		git_config_set("core.repositoryformatversion", "1");

		/* Add promisor config for the remote */
		cfg_name = xstrfmt("remote.%s.promisor", remote);
		git_config_set(cfg_name, "true");
		free(cfg_name);
	}

	/*
	 * Record the initial filter-spec in the config as
	 * the default for subsequent fetches from this remote.
	 */
	filter_name = xstrfmt("remote.%s.partialclonefilter", remote);
	/* NEEDSWORK: 'expand' result leaking??? */
	git_config_set(filter_name,
		       expand_list_objects_filter_spec(filter_options));
	free(filter_name);

	/* Make sure the config info are reset */
	promisor_remote_reinit();
}