#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct setup_revision_opt {char* submodule; int revarg_opt; int /*<<< orphan*/  (* tweak ) (struct rev_info*,struct setup_revision_opt*) ;int /*<<< orphan*/ * def; scalar_t__ assume_dashdash; } ;
struct TYPE_12__ {scalar_t__ follow_renames; } ;
struct TYPE_16__ {int output_format; int pickaxe_opts; int /*<<< orphan*/  abbrev; int /*<<< orphan*/  pathspec; TYPE_3__ flags; scalar_t__ objfind; scalar_t__ filter; } ;
struct TYPE_15__ {int ignore_locale; scalar_t__ use_reflog_filter; } ;
struct TYPE_13__ {scalar_t__ name; } ;
struct TYPE_14__ {scalar_t__ nr; } ;
struct TYPE_11__ {int /*<<< orphan*/  pathspec; } ;
struct TYPE_10__ {int /*<<< orphan*/  nr; } ;
struct rev_info {int diff; int topo_order; int limited; int prune; scalar_t__ expand_tabs_in_log; scalar_t__ expand_tabs_in_log_default; TYPE_7__ diffopt; scalar_t__ line_level_traverse; scalar_t__ bisect; scalar_t__ first_parent_only; TYPE_6__ grep_filter; scalar_t__ reflog_info; scalar_t__ graph; scalar_t__ no_walk; scalar_t__ reverse; TYPE_4__ children; scalar_t__ rewrite_parents; int /*<<< orphan*/  abbrev; scalar_t__ combine_merges; scalar_t__ combined_all_paths; scalar_t__ ignore_merges; TYPE_5__ prune_data; int /*<<< orphan*/  full_diff; TYPE_2__ pruning; scalar_t__ simplify_history; int /*<<< orphan*/ * def; int /*<<< orphan*/  repo; int /*<<< orphan*/  rev_input_given; TYPE_1__ pending; scalar_t__ show_merge; int /*<<< orphan*/  prefix; int /*<<< orphan*/  read_from_stdin; scalar_t__ disable_stdin; } ;
struct object_id {int dummy; } ;
struct object_context {int /*<<< orphan*/  mode; } ;
struct object {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argv; scalar_t__ argc; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int DIFF_FORMAT_NO_OUTPUT ; 
 int DIFF_FORMAT_PATCH ; 
 int DIFF_PICKAXE_KINDS_MASK ; 
 int /*<<< orphan*/  GREP_PATTERN_TYPE_UNSPECIFIED ; 
 int REVARG_CANNOT_BE_FILENAME ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_pending_object_with_mode (struct rev_info*,struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pushv (struct argv_array*,char const**) ; 
 int /*<<< orphan*/  compile_grep_patterns (TYPE_6__*) ; 
 int /*<<< orphan*/  copy_pathspec (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  diagnose_missing_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  diff_setup_done (TYPE_7__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  generation_numbers_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_log_output_encoding () ; 
 scalar_t__ get_oid_with_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct object_id*,struct object_context*) ; 
 struct object* get_reference (struct rev_info*,int /*<<< orphan*/ *,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grep_commit_pattern_type (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ handle_revision_arg (char const*,struct rev_info*,int,int) ; 
 int handle_revision_opt (struct rev_info*,int,char const**,int*,char const**,struct setup_revision_opt*) ; 
 int handle_revision_pseudo_opt (char const*,struct rev_info*,int,char const**,int*) ; 
 int /*<<< orphan*/  is_encoding_utf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_pathspec (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_show_merge (struct rev_info*) ; 
 int /*<<< orphan*/  read_revisions_from_stdin (struct rev_info*,struct argv_array*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (struct rev_info*,struct setup_revision_opt*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  verify_filename (int /*<<< orphan*/ ,char const*,int) ; 

int setup_revisions(int argc, const char **argv, struct rev_info *revs, struct setup_revision_opt *opt)
{
	int i, flags, left, seen_dashdash, got_rev_arg = 0, revarg_opt;
	struct argv_array prune_data = ARGV_ARRAY_INIT;
	const char *submodule = NULL;
	int seen_end_of_options = 0;

	if (opt)
		submodule = opt->submodule;

	/* First, search for "--" */
	if (opt && opt->assume_dashdash) {
		seen_dashdash = 1;
	} else {
		seen_dashdash = 0;
		for (i = 1; i < argc; i++) {
			const char *arg = argv[i];
			if (strcmp(arg, "--"))
				continue;
			argv[i] = NULL;
			argc = i;
			if (argv[i + 1])
				argv_array_pushv(&prune_data, argv + i + 1);
			seen_dashdash = 1;
			break;
		}
	}

	/* Second, deal with arguments and options */
	flags = 0;
	revarg_opt = opt ? opt->revarg_opt : 0;
	if (seen_dashdash)
		revarg_opt |= REVARG_CANNOT_BE_FILENAME;
	for (left = i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!seen_end_of_options && *arg == '-') {
			int opts;

			opts = handle_revision_pseudo_opt(submodule,
						revs, argc - i, argv + i,
						&flags);
			if (opts > 0) {
				i += opts - 1;
				continue;
			}

			if (!strcmp(arg, "--stdin")) {
				if (revs->disable_stdin) {
					argv[left++] = arg;
					continue;
				}
				if (revs->read_from_stdin++)
					die("--stdin given twice?");
				read_revisions_from_stdin(revs, &prune_data);
				continue;
			}

			if (!strcmp(arg, "--end-of-options")) {
				seen_end_of_options = 1;
				continue;
			}

			opts = handle_revision_opt(revs, argc - i, argv + i,
						   &left, argv, opt);
			if (opts > 0) {
				i += opts - 1;
				continue;
			}
			if (opts < 0)
				exit(128);
			continue;
		}


		if (handle_revision_arg(arg, revs, flags, revarg_opt)) {
			int j;
			if (seen_dashdash || *arg == '^')
				die("bad revision '%s'", arg);

			/* If we didn't have a "--":
			 * (1) all filenames must exist;
			 * (2) all rev-args must not be interpretable
			 *     as a valid filename.
			 * but the latter we have checked in the main loop.
			 */
			for (j = i; j < argc; j++)
				verify_filename(revs->prefix, argv[j], j == i);

			argv_array_pushv(&prune_data, argv + i);
			break;
		}
		else
			got_rev_arg = 1;
	}

	if (prune_data.argc) {
		/*
		 * If we need to introduce the magic "a lone ':' means no
		 * pathspec whatsoever", here is the place to do so.
		 *
		 * if (prune_data.nr == 1 && !strcmp(prune_data[0], ":")) {
		 *	prune_data.nr = 0;
		 *	prune_data.alloc = 0;
		 *	free(prune_data.path);
		 *	prune_data.path = NULL;
		 * } else {
		 *	terminate prune_data.alloc with NULL and
		 *	call init_pathspec() to set revs->prune_data here.
		 * }
		 */
		parse_pathspec(&revs->prune_data, 0, 0,
			       revs->prefix, prune_data.argv);
	}
	argv_array_clear(&prune_data);

	if (revs->def == NULL)
		revs->def = opt ? opt->def : NULL;
	if (opt && opt->tweak)
		opt->tweak(revs, opt);
	if (revs->show_merge)
		prepare_show_merge(revs);
	if (revs->def && !revs->pending.nr && !revs->rev_input_given && !got_rev_arg) {
		struct object_id oid;
		struct object *object;
		struct object_context oc;
		if (get_oid_with_context(revs->repo, revs->def, 0, &oid, &oc))
			diagnose_missing_default(revs->def);
		object = get_reference(revs, revs->def, &oid, 0);
		add_pending_object_with_mode(revs, object, revs->def, oc.mode);
	}

	/* Did the user ask for any diff output? Run the diff! */
	if (revs->diffopt.output_format & ~DIFF_FORMAT_NO_OUTPUT)
		revs->diff = 1;

	/* Pickaxe, diff-filter and rename following need diffs */
	if ((revs->diffopt.pickaxe_opts & DIFF_PICKAXE_KINDS_MASK) ||
	    revs->diffopt.filter ||
	    revs->diffopt.flags.follow_renames)
		revs->diff = 1;

	if (revs->diffopt.objfind)
		revs->simplify_history = 0;

	if (revs->topo_order && !generation_numbers_enabled(the_repository))
		revs->limited = 1;

	if (revs->prune_data.nr) {
		copy_pathspec(&revs->pruning.pathspec, &revs->prune_data);
		/* Can't prune commits with rename following: the paths change.. */
		if (!revs->diffopt.flags.follow_renames)
			revs->prune = 1;
		if (!revs->full_diff)
			copy_pathspec(&revs->diffopt.pathspec,
				      &revs->prune_data);
	}
	if (revs->combine_merges)
		revs->ignore_merges = 0;
	if (revs->combined_all_paths && !revs->combine_merges)
		die("--combined-all-paths makes no sense without -c or --cc");

	revs->diffopt.abbrev = revs->abbrev;

	if (revs->line_level_traverse) {
		revs->limited = 1;
		revs->topo_order = 1;
	}

	diff_setup_done(&revs->diffopt);

	grep_commit_pattern_type(GREP_PATTERN_TYPE_UNSPECIFIED,
				 &revs->grep_filter);
	if (!is_encoding_utf8(get_log_output_encoding()))
		revs->grep_filter.ignore_locale = 1;
	compile_grep_patterns(&revs->grep_filter);

	if (revs->reverse && revs->reflog_info)
		die("cannot combine --reverse with --walk-reflogs");
	if (revs->reflog_info && revs->limited)
		die("cannot combine --walk-reflogs with history-limiting options");
	if (revs->rewrite_parents && revs->children.name)
		die("cannot combine --parents and --children");

	/*
	 * Limitations on the graph functionality
	 */
	if (revs->reverse && revs->graph)
		die("cannot combine --reverse with --graph");

	if (revs->reflog_info && revs->graph)
		die("cannot combine --walk-reflogs with --graph");
	if (revs->no_walk && revs->graph)
		die("cannot combine --no-walk with --graph");
	if (!revs->reflog_info && revs->grep_filter.use_reflog_filter)
		die("cannot use --grep-reflog without --walk-reflogs");

	if (revs->first_parent_only && revs->bisect)
		die(_("--first-parent is incompatible with --bisect"));

	if (revs->line_level_traverse &&
	    (revs->diffopt.output_format & ~(DIFF_FORMAT_PATCH | DIFF_FORMAT_NO_OUTPUT)))
		die(_("-L does not yet support diff formats besides -p and -s"));

	if (revs->expand_tabs_in_log < 0)
		revs->expand_tabs_in_log = revs->expand_tabs_in_log_default;

	return left;
}