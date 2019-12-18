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
struct TYPE_2__ {int core_commit_graph; int gc_write_commit_graph; int index_version; int core_untracked_cache; int fetch_negotiation_algorithm; int pack_use_sparse; int fetch_write_commit_graph; scalar_t__ initialized; } ;
struct repository {TYPE_1__ settings; } ;

/* Variables and functions */
 int FETCH_NEGOTIATION_DEFAULT ; 
 int FETCH_NEGOTIATION_SKIPPING ; 
 int UNTRACKED_CACHE_KEEP ; 
 int UNTRACKED_CACHE_REMOVE ; 
 int UNTRACKED_CACHE_WRITE ; 
 int /*<<< orphan*/  UPDATE_DEFAULT_BOOL (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ignore_untracked_cache_config ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  repo_config_get_bool (struct repository*,char*,int*) ; 
 int /*<<< orphan*/  repo_config_get_int (struct repository*,char*,int*) ; 
 int /*<<< orphan*/  repo_config_get_maybe_bool (struct repository*,char*,int*) ; 
 int /*<<< orphan*/  repo_config_get_string (struct repository*,char*,char**) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

void prepare_repo_settings(struct repository *r)
{
	int value;
	char *strval;

	if (r->settings.initialized)
		return;

	/* Defaults */
	memset(&r->settings, -1, sizeof(r->settings));

	if (!repo_config_get_bool(r, "core.commitgraph", &value))
		r->settings.core_commit_graph = value;
	if (!repo_config_get_bool(r, "gc.writecommitgraph", &value))
		r->settings.gc_write_commit_graph = value;
	UPDATE_DEFAULT_BOOL(r->settings.core_commit_graph, 1);
	UPDATE_DEFAULT_BOOL(r->settings.gc_write_commit_graph, 1);

	if (!repo_config_get_int(r, "index.version", &value))
		r->settings.index_version = value;
	if (!repo_config_get_maybe_bool(r, "core.untrackedcache", &value)) {
		if (value == 0)
			r->settings.core_untracked_cache = UNTRACKED_CACHE_REMOVE;
		else
			r->settings.core_untracked_cache = UNTRACKED_CACHE_WRITE;
	} else if (!repo_config_get_string(r, "core.untrackedcache", &strval)) {
		if (!strcasecmp(strval, "keep"))
			r->settings.core_untracked_cache = UNTRACKED_CACHE_KEEP;

		free(strval);
	}

	if (!repo_config_get_string(r, "fetch.negotiationalgorithm", &strval)) {
		if (!strcasecmp(strval, "skipping"))
			r->settings.fetch_negotiation_algorithm = FETCH_NEGOTIATION_SKIPPING;
		else
			r->settings.fetch_negotiation_algorithm = FETCH_NEGOTIATION_DEFAULT;
	}

	if (!repo_config_get_bool(r, "pack.usesparse", &value))
		r->settings.pack_use_sparse = value;
	if (!repo_config_get_bool(r, "feature.manyfiles", &value) && value) {
		UPDATE_DEFAULT_BOOL(r->settings.index_version, 4);
		UPDATE_DEFAULT_BOOL(r->settings.core_untracked_cache, UNTRACKED_CACHE_WRITE);
	}
	if (!repo_config_get_bool(r, "fetch.writecommitgraph", &value))
		r->settings.fetch_write_commit_graph = value;
	if (!repo_config_get_bool(r, "feature.experimental", &value) && value) {
		UPDATE_DEFAULT_BOOL(r->settings.pack_use_sparse, 1);
		UPDATE_DEFAULT_BOOL(r->settings.fetch_negotiation_algorithm, FETCH_NEGOTIATION_SKIPPING);
		UPDATE_DEFAULT_BOOL(r->settings.fetch_write_commit_graph, 1);
	}
	UPDATE_DEFAULT_BOOL(r->settings.fetch_write_commit_graph, 0);

	/* Hack for test programs like test-dump-untracked-cache */
	if (ignore_untracked_cache_config)
		r->settings.core_untracked_cache = UNTRACKED_CACHE_KEEP;
	else
		UPDATE_DEFAULT_BOOL(r->settings.core_untracked_cache, UNTRACKED_CACHE_KEEP);

	UPDATE_DEFAULT_BOOL(r->settings.fetch_negotiation_algorithm, FETCH_NEGOTIATION_DEFAULT);
}