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
struct log_state {int max_parents; int limit; int skip; int min_parents; int show_diff; int show_log_size; int /*<<< orphan*/  repodir; int /*<<< orphan*/  grep; int /*<<< orphan*/  committer; int /*<<< orphan*/  author; int /*<<< orphan*/  revisions; int /*<<< orphan*/  sorting; } ;
struct log_options {int max_parents; int limit; int skip; int min_parents; int show_diff; int show_log_size; int /*<<< orphan*/  repodir; int /*<<< orphan*/  grep; int /*<<< orphan*/  committer; int /*<<< orphan*/  author; int /*<<< orphan*/  revisions; int /*<<< orphan*/  sorting; } ;
struct args_info {int pos; } ;

/* Variables and functions */
 struct args_info ARGS_INFO_INIT ; 
 int /*<<< orphan*/  GIT_SORT_REVERSE ; 
 int /*<<< orphan*/  GIT_SORT_TIME ; 
 int /*<<< orphan*/  GIT_SORT_TOPOLOGICAL ; 
 int /*<<< orphan*/  add_revision (struct log_state*,char const*) ; 
 int /*<<< orphan*/  is_integer (int*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_int_arg (int*,struct args_info*,char*,int) ; 
 scalar_t__ match_str_arg (int /*<<< orphan*/ *,struct args_info*,char*) ; 
 int /*<<< orphan*/  memset (struct log_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_sorting (struct log_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char*,char const*) ; 

__attribute__((used)) static int parse_options(
	struct log_state *s, struct log_options *opt, int argc, char **argv)
{
	struct args_info args = ARGS_INFO_INIT;

	memset(s, 0, sizeof(*s));
	s->sorting = GIT_SORT_TIME;

	memset(opt, 0, sizeof(*opt));
	opt->max_parents = -1;
	opt->limit = -1;

	for (args.pos = 1; args.pos < argc; ++args.pos) {
		const char *a = argv[args.pos];

		if (a[0] != '-') {
			if (!add_revision(s, a))
				s->revisions++;
			else
				/** Try failed revision parse as filename. */
				break;
		} else if (!strcmp(a, "--")) {
			++args.pos;
			break;
		}
		else if (!strcmp(a, "--date-order"))
			set_sorting(s, GIT_SORT_TIME);
		else if (!strcmp(a, "--topo-order"))
			set_sorting(s, GIT_SORT_TOPOLOGICAL);
		else if (!strcmp(a, "--reverse"))
			set_sorting(s, GIT_SORT_REVERSE);
		else if (match_str_arg(&opt->author, &args, "--author"))
			/** Found valid --author */;
		else if (match_str_arg(&opt->committer, &args, "--committer"))
			/** Found valid --committer */;
		else if (match_str_arg(&opt->grep, &args, "--grep"))
			/** Found valid --grep */;
		else if (match_str_arg(&s->repodir, &args, "--git-dir"))
			/** Found git-dir. */;
		else if (match_int_arg(&opt->skip, &args, "--skip", 0))
			/** Found valid --skip. */;
		else if (match_int_arg(&opt->limit, &args, "--max-count", 0))
			/** Found valid --max-count. */;
		else if (a[1] >= '0' && a[1] <= '9')
			is_integer(&opt->limit, a + 1, 0);
		else if (match_int_arg(&opt->limit, &args, "-n", 0))
			/** Found valid -n. */;
		else if (!strcmp(a, "--merges"))
			opt->min_parents = 2;
		else if (!strcmp(a, "--no-merges"))
			opt->max_parents = 1;
		else if (!strcmp(a, "--no-min-parents"))
			opt->min_parents = 0;
		else if (!strcmp(a, "--no-max-parents"))
			opt->max_parents = -1;
		else if (match_int_arg(&opt->max_parents, &args, "--max-parents=", 1))
			/** Found valid --max-parents. */;
		else if (match_int_arg(&opt->min_parents, &args, "--min-parents=", 0))
			/** Found valid --min_parents. */;
		else if (!strcmp(a, "-p") || !strcmp(a, "-u") || !strcmp(a, "--patch"))
			opt->show_diff = 1;
		else if (!strcmp(a, "--log-size"))
			opt->show_log_size = 1;
		else
			usage("Unsupported argument", a);
	}

	return args.pos;
}