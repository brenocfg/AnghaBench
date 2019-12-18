#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int core_commit_graph; } ;
struct repository {TYPE_2__* objects; TYPE_1__ settings; scalar_t__ commit_graph_disabled; } ;
struct object_directory {int /*<<< orphan*/  path; struct object_directory* next; } ;
struct TYPE_4__ {int commit_graph_attempted; int /*<<< orphan*/  commit_graph; struct object_directory* odb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_TEST_COMMIT_GRAPH ; 
 int /*<<< orphan*/  GIT_TEST_COMMIT_GRAPH_DIE_ON_LOAD ; 
 int /*<<< orphan*/  commit_graph_compatible (struct repository*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_env_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_alt_odb (struct repository*) ; 
 int /*<<< orphan*/  prepare_commit_graph_one (struct repository*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_repo_settings (struct repository*) ; 

__attribute__((used)) static int prepare_commit_graph(struct repository *r)
{
	struct object_directory *odb;

	/*
	 * This must come before the "already attempted?" check below, because
	 * we want to disable even an already-loaded graph file.
	 */
	if (r->commit_graph_disabled)
		return 0;

	if (r->objects->commit_graph_attempted)
		return !!r->objects->commit_graph;
	r->objects->commit_graph_attempted = 1;

	if (git_env_bool(GIT_TEST_COMMIT_GRAPH_DIE_ON_LOAD, 0))
		die("dying as requested by the '%s' variable on commit-graph load!",
		    GIT_TEST_COMMIT_GRAPH_DIE_ON_LOAD);

	prepare_repo_settings(r);

	if (!git_env_bool(GIT_TEST_COMMIT_GRAPH, 0) &&
	    r->settings.core_commit_graph != 1)
		/*
		 * This repository is not configured to use commit graphs, so
		 * do not load one. (But report commit_graph_attempted anyway
		 * so that commit graph loading is not attempted again for this
		 * repository.)
		 */
		return 0;

	if (!commit_graph_compatible(r))
		return 0;

	prepare_alt_odb(r);
	for (odb = r->objects->odb;
	     !r->objects->commit_graph && odb;
	     odb = odb->next)
		prepare_commit_graph_one(r, odb->path);
	return !!r->objects->commit_graph;
}