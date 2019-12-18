#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct setup_revision_opt {int /*<<< orphan*/  tweak; } ;
struct TYPE_9__ {int needed_rename_limit; int degraded_cc_to_c; int /*<<< orphan*/  setup; scalar_t__ detect_rename; } ;
struct TYPE_7__ {int nr; TYPE_1__* objects; } ;
struct rev_info {int diff; int disable_stdin; TYPE_4__ diffopt; TYPE_2__ pending; scalar_t__ abbrev; } ;
struct object_id {int dummy; } ;
struct object {int flags; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  s_r_opt ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_8__ {int /*<<< orphan*/  cache; } ;
struct TYPE_6__ {struct object* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SETUP_USE_SIZE_CACHE ; 
 int /*<<< orphan*/  SWAP (struct object*,struct object*) ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int diff_result_code (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_tree_commit_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  diff_tree_stdin (char*) ; 
 int /*<<< orphan*/  diff_tree_tweak_rev ; 
 int /*<<< orphan*/  diff_tree_usage ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_basic_config ; 
 int /*<<< orphan*/  log_tree_diff_flush (struct rev_info*) ; 
 struct rev_info log_tree_opt ; 
 int /*<<< orphan*/  memset (struct setup_revision_opt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  precompose_argv (int,char const**) ; 
 scalar_t__ read_cache () ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 int /*<<< orphan*/  repo_read_index (int /*<<< orphan*/ ) ; 
 int setup_revisions (int,char const**,struct rev_info*,struct setup_revision_opt*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 TYPE_3__ the_index ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int cmd_diff_tree(int argc, const char **argv, const char *prefix)
{
	char line[1000];
	struct object *tree1, *tree2;
	static struct rev_info *opt = &log_tree_opt;
	struct setup_revision_opt s_r_opt;
	int read_stdin = 0;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(diff_tree_usage);

	git_config(git_diff_basic_config, NULL); /* no "diff" UI options */
	repo_init_revisions(the_repository, opt, prefix);
	if (read_cache() < 0)
		die(_("index file corrupt"));
	opt->abbrev = 0;
	opt->diff = 1;
	opt->disable_stdin = 1;
	memset(&s_r_opt, 0, sizeof(s_r_opt));
	s_r_opt.tweak = diff_tree_tweak_rev;

	precompose_argv(argc, argv);
	argc = setup_revisions(argc, argv, opt, &s_r_opt);

	while (--argc > 0) {
		const char *arg = *++argv;

		if (!strcmp(arg, "--stdin")) {
			read_stdin = 1;
			continue;
		}
		usage(diff_tree_usage);
	}

	/*
	 * NOTE!  We expect "a..b" to expand to "^a b" but it is
	 * perfectly valid for revision range parser to yield "b ^a",
	 * which means the same thing. If we get the latter, i.e. the
	 * second one is marked UNINTERESTING, we recover the original
	 * order the user gave, i.e. "a..b", by swapping the trees.
	 */
	switch (opt->pending.nr) {
	case 0:
		if (!read_stdin)
			usage(diff_tree_usage);
		break;
	case 1:
		tree1 = opt->pending.objects[0].item;
		diff_tree_commit_oid(&tree1->oid);
		break;
	case 2:
		tree1 = opt->pending.objects[0].item;
		tree2 = opt->pending.objects[1].item;
		if (tree2->flags & UNINTERESTING) {
			SWAP(tree2, tree1);
		}
		diff_tree_oid(&tree1->oid, &tree2->oid, "", &opt->diffopt);
		log_tree_diff_flush(opt);
		break;
	}

	if (read_stdin) {
		int saved_nrl = 0;
		int saved_dcctc = 0;

		if (opt->diffopt.detect_rename) {
			if (!the_index.cache)
				repo_read_index(the_repository);
			opt->diffopt.setup |= DIFF_SETUP_USE_SIZE_CACHE;
		}
		while (fgets(line, sizeof(line), stdin)) {
			struct object_id oid;

			if (get_oid_hex(line, &oid)) {
				fputs(line, stdout);
				fflush(stdout);
			}
			else {
				diff_tree_stdin(line);
				if (saved_nrl < opt->diffopt.needed_rename_limit)
					saved_nrl = opt->diffopt.needed_rename_limit;
				if (opt->diffopt.degraded_cc_to_c)
					saved_dcctc = 1;
			}
		}
		opt->diffopt.degraded_cc_to_c = saved_dcctc;
		opt->diffopt.needed_rename_limit = saved_nrl;
	}

	return diff_result_code(&opt->diffopt, 0);
}