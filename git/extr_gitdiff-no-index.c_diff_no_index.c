#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct TYPE_9__ {int no_index; int relative_name; int exit_with_status; } ;
struct TYPE_10__ {int skip_stat_unmatch; char const* prefix; TYPE_1__ flags; scalar_t__ output_format; int /*<<< orphan*/  parseopts; } ;
struct rev_info {char* prefix; int max_count; TYPE_2__ diffopt; } ;
struct option {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIFF_FORMAT_PATCH ; 
 int /*<<< orphan*/  FREE_AND_NULL (struct option*) ; 
 struct option OPT_BOOL_F (int /*<<< orphan*/ ,char*,int*,char*,int) ; 
 struct option OPT_END () ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_NONEG ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  diff_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  diff_no_index_usage ; 
 int diff_result_code (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_set_mnemonic_prefix (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  diff_setup_done (TYPE_2__*) ; 
 int /*<<< orphan*/  diffcore_std (TYPE_2__*) ; 
 char* file_from_standard_input ; 
 int /*<<< orphan*/  fixup_paths (char const**,struct strbuf*) ; 
 int parse_options (int,char const**,char*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option* parse_options_concat (struct option*,int /*<<< orphan*/ ) ; 
 char* prefix_filename (char const*,char const*) ; 
 scalar_t__ queue_diff (TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  setup_diff_pager (TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

int diff_no_index(struct rev_info *revs,
		  int implicit_no_index,
		  int argc, const char **argv)
{
	int i, no_index;
	const char *paths[2];
	struct strbuf replacement = STRBUF_INIT;
	const char *prefix = revs->prefix;
	struct option no_index_options[] = {
		OPT_BOOL_F(0, "no-index", &no_index, "",
			   PARSE_OPT_NONEG | PARSE_OPT_HIDDEN),
		OPT_END(),
	};
	struct option *options;

	options = parse_options_concat(no_index_options,
				       revs->diffopt.parseopts);
	argc = parse_options(argc, argv, revs->prefix, options,
			     diff_no_index_usage, 0);
	if (argc != 2) {
		if (implicit_no_index)
			warning(_("Not a git repository. Use --no-index to "
				  "compare two paths outside a working tree"));
		usage_with_options(diff_no_index_usage, options);
	}
	FREE_AND_NULL(options);
	for (i = 0; i < 2; i++) {
		const char *p = argv[argc - 2 + i];
		if (!strcmp(p, "-"))
			/*
			 * stdin should be spelled as "-"; if you have
			 * path that is "-", spell it as "./-".
			 */
			p = file_from_standard_input;
		else if (prefix)
			p = prefix_filename(prefix, p);
		paths[i] = p;
	}

	fixup_paths(paths, &replacement);

	revs->diffopt.skip_stat_unmatch = 1;
	if (!revs->diffopt.output_format)
		revs->diffopt.output_format = DIFF_FORMAT_PATCH;

	revs->diffopt.flags.no_index = 1;

	revs->diffopt.flags.relative_name = 1;
	revs->diffopt.prefix = prefix;

	revs->max_count = -2;
	diff_setup_done(&revs->diffopt);

	setup_diff_pager(&revs->diffopt);
	revs->diffopt.flags.exit_with_status = 1;

	if (queue_diff(&revs->diffopt, paths[0], paths[1]))
		return 1;
	diff_set_mnemonic_prefix(&revs->diffopt, "1/", "2/");
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);

	strbuf_release(&replacement);

	/*
	 * The return code for --no-index imitates diff(1):
	 * 0 = no changes, 1 = changes, else error
	 */
	return diff_result_code(&revs->diffopt, 0);
}