#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; } ;
struct split_commit_graph_opts {int dummy; } ;
struct remote {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;
struct TYPE_11__ {scalar_t__ nr; } ;
struct TYPE_10__ {scalar_t__ choice; } ;
struct TYPE_8__ {scalar_t__ fetch_write_commit_graph; } ;
struct TYPE_9__ {int /*<<< orphan*/  objects; TYPE_1__ settings; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int COMMIT_GRAPH_WRITE_PROGRESS ; 
 int COMMIT_GRAPH_WRITE_SPLIT ; 
 scalar_t__ INFINITE_DEPTH ; 
 scalar_t__ RECURSE_SUBMODULES_OFF ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_options_to_argv (struct argv_array*) ; 
 int /*<<< orphan*/  add_remote_or_group (char const*,struct string_list*) ; 
 scalar_t__ all ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char*,int /*<<< orphan*/ *) ; 
 int atoi (scalar_t__) ; 
 int /*<<< orphan*/  builtin_fetch_options ; 
 int /*<<< orphan*/  builtin_fetch_usage ; 
 int /*<<< orphan*/  close_object_store (int /*<<< orphan*/ ) ; 
 int deepen ; 
 TYPE_7__ deepen_not ; 
 scalar_t__ deepen_relative ; 
 scalar_t__ deepen_since ; 
 int /*<<< orphan*/  default_rla ; 
 scalar_t__ depth ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ enable_auto_gc ; 
 int /*<<< orphan*/  fetch_config_from_gitmodules (int*,scalar_t__*) ; 
 scalar_t__ fetch_if_missing ; 
 int fetch_multiple (struct string_list*,int) ; 
 int fetch_one (struct remote*,int,char const**,int) ; 
 int /*<<< orphan*/  fetch_one_setup_partial (struct remote*) ; 
 int fetch_parallel_config ; 
 int fetch_populated_submodules (TYPE_2__*,struct argv_array*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__ filter_options ; 
 int /*<<< orphan*/  for_each_remote (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  get_object_directory () ; 
 int /*<<< orphan*/  get_one_remote_for_fetch ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_fetch_config ; 
 scalar_t__ has_promisor_remote () ; 
 int /*<<< orphan*/  is_repository_shallow (TYPE_2__*) ; 
 int max_jobs ; 
 int /*<<< orphan*/  memset (struct split_commit_graph_opts*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ multiple ; 
 int /*<<< orphan*/  packet_trace_identity (char*) ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_repo_settings (TYPE_2__*) ; 
 scalar_t__ progress ; 
 scalar_t__ recurse_submodules ; 
 int /*<<< orphan*/  recurse_submodules_default ; 
 struct remote* remote_get (char const*) ; 
 int /*<<< orphan*/  run_command_v_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int submodule_fetch_jobs_config ; 
 int /*<<< orphan*/  submodule_prefix ; 
 TYPE_2__* the_repository ; 
 scalar_t__ unshallow ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_commit_graph_reachable (int /*<<< orphan*/ ,int,struct split_commit_graph_opts*) ; 
 scalar_t__ xstrfmt (char*,scalar_t__) ; 

int cmd_fetch(int argc, const char **argv, const char *prefix)
{
	int i;
	struct string_list list = STRING_LIST_INIT_DUP;
	struct remote *remote = NULL;
	int result = 0;
	int prune_tags_ok = 1;
	struct argv_array argv_gc_auto = ARGV_ARRAY_INIT;

	packet_trace_identity("fetch");

	/* Record the command line for the reflog */
	strbuf_addstr(&default_rla, "fetch");
	for (i = 1; i < argc; i++)
		strbuf_addf(&default_rla, " %s", argv[i]);

	fetch_config_from_gitmodules(&submodule_fetch_jobs_config,
				     &recurse_submodules);
	git_config(git_fetch_config, NULL);

	argc = parse_options(argc, argv, prefix,
			     builtin_fetch_options, builtin_fetch_usage, 0);

	if (deepen_relative) {
		if (deepen_relative < 0)
			die(_("Negative depth in --deepen is not supported"));
		if (depth)
			die(_("--deepen and --depth are mutually exclusive"));
		depth = xstrfmt("%d", deepen_relative);
	}
	if (unshallow) {
		if (depth)
			die(_("--depth and --unshallow cannot be used together"));
		else if (!is_repository_shallow(the_repository))
			die(_("--unshallow on a complete repository does not make sense"));
		else
			depth = xstrfmt("%d", INFINITE_DEPTH);
	}

	/* no need to be strict, transport_set_option() will validate it again */
	if (depth && atoi(depth) < 1)
		die(_("depth %s is not a positive number"), depth);
	if (depth || deepen_since || deepen_not.nr)
		deepen = 1;

	if (filter_options.choice && !has_promisor_remote())
		die("--filter can only be used when extensions.partialClone is set");

	if (all) {
		if (argc == 1)
			die(_("fetch --all does not take a repository argument"));
		else if (argc > 1)
			die(_("fetch --all does not make sense with refspecs"));
		(void) for_each_remote(get_one_remote_for_fetch, &list);
	} else if (argc == 0) {
		/* No arguments -- use default remote */
		remote = remote_get(NULL);
	} else if (multiple) {
		/* All arguments are assumed to be remotes or groups */
		for (i = 0; i < argc; i++)
			if (!add_remote_or_group(argv[i], &list))
				die(_("No such remote or remote group: %s"), argv[i]);
	} else {
		/* Single remote or group */
		(void) add_remote_or_group(argv[0], &list);
		if (list.nr > 1) {
			/* More than one remote */
			if (argc > 1)
				die(_("Fetching a group and specifying refspecs does not make sense"));
		} else {
			/* Zero or one remotes */
			remote = remote_get(argv[0]);
			prune_tags_ok = (argc == 1);
			argc--;
			argv++;
		}
	}

	fetch_if_missing = 0;

	if (remote) {
		if (filter_options.choice || has_promisor_remote())
			fetch_one_setup_partial(remote);
		result = fetch_one(remote, argc, argv, prune_tags_ok);
	} else {
		int max_children = max_jobs;

		if (filter_options.choice)
			die(_("--filter can only be used with the remote "
			      "configured in extensions.partialclone"));

		if (max_children < 0)
			max_children = fetch_parallel_config;

		/* TODO should this also die if we have a previous partial-clone? */
		result = fetch_multiple(&list, max_children);
	}

	if (!result && (recurse_submodules != RECURSE_SUBMODULES_OFF)) {
		struct argv_array options = ARGV_ARRAY_INIT;
		int max_children = max_jobs;

		if (max_children < 0)
			max_children = submodule_fetch_jobs_config;
		if (max_children < 0)
			max_children = fetch_parallel_config;

		add_options_to_argv(&options);
		result = fetch_populated_submodules(the_repository,
						    &options,
						    submodule_prefix,
						    recurse_submodules,
						    recurse_submodules_default,
						    verbosity < 0,
						    max_children);
		argv_array_clear(&options);
	}

	string_list_clear(&list, 0);

	prepare_repo_settings(the_repository);
	if (the_repository->settings.fetch_write_commit_graph) {
		int commit_graph_flags = COMMIT_GRAPH_WRITE_SPLIT;
		struct split_commit_graph_opts split_opts;
		memset(&split_opts, 0, sizeof(struct split_commit_graph_opts));

		if (progress)
			commit_graph_flags |= COMMIT_GRAPH_WRITE_PROGRESS;

		write_commit_graph_reachable(get_object_directory(),
					     commit_graph_flags,
					     &split_opts);
	}

	close_object_store(the_repository->objects);

	if (enable_auto_gc) {
		argv_array_pushl(&argv_gc_auto, "gc", "--auto", NULL);
		if (verbosity < 0)
			argv_array_push(&argv_gc_auto, "--quiet");
		run_command_v_opt(argv_gc_auto.argv, RUN_GIT_CMD);
		argv_array_clear(&argv_gc_auto);
	}

	return result;
}