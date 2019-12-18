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
struct repository {scalar_t__ config; int /*<<< orphan*/  gitdir; int /*<<< orphan*/  commondir; } ;
struct config_set {int dummy; } ;
struct config_options {int respect_includes; int /*<<< orphan*/  git_dir; int /*<<< orphan*/  commondir; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  config_set_callback ; 
 scalar_t__ config_with_options (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct config_options*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_configset_clear (scalar_t__) ; 
 int /*<<< orphan*/  git_configset_init (scalar_t__) ; 
 scalar_t__ xcalloc (int,int) ; 

__attribute__((used)) static void repo_read_config(struct repository *repo)
{
	struct config_options opts = { 0 };

	opts.respect_includes = 1;
	opts.commondir = repo->commondir;
	opts.git_dir = repo->gitdir;

	if (!repo->config)
		repo->config = xcalloc(1, sizeof(struct config_set));
	else
		git_configset_clear(repo->config);

	git_configset_init(repo->config);

	if (config_with_options(config_set_callback, repo->config, NULL, &opts) < 0)
		/*
		 * config_with_options() normally returns only
		 * zero, as most errors are fatal, and
		 * non-fatal potential errors are guarded by "if"
		 * statements that are entered only when no error is
		 * possible.
		 *
		 * If we ever encounter a non-fatal error, it means
		 * something went really wrong and we should stop
		 * immediately.
		 */
		die(_("unknown error occurred while reading the configuration files"));
}