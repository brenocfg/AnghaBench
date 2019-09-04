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
struct option {char member_1; char* member_2; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/ * member_4; struct apply_state* member_3; int /*<<< orphan*/  member_0; } ;
struct apply_state {int no_add; int diffstat; int numstat; int summary; int check; int check_index; int ita_only; int cached; int threeway; int apply_in_reverse; int unidiff_zero; int apply_with_reject; int allow_overlap; int /*<<< orphan*/  prefix; int /*<<< orphan*/  apply_verbosity; int /*<<< orphan*/  p_context; int /*<<< orphan*/  line_termination; int /*<<< orphan*/  fake_ancestor; int /*<<< orphan*/  unsafe_paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLY_OPT_INACCURATE_EOF ; 
 int /*<<< orphan*/  APPLY_OPT_RECOUNT ; 
 int /*<<< orphan*/ * N_ (char*) ; 
 int /*<<< orphan*/  OPTION_CALLBACK ; 
 struct option OPT_BIT (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ *) ; 
 struct option OPT_BOOL_F (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_FILENAME (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct option OPT_INTEGER (char,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct option OPT_NOOP_NOARG (int /*<<< orphan*/ ,char*) ; 
 struct option OPT_SET_INT (char,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 struct option OPT__VERBOSE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARSE_OPT_NOARG ; 
 int /*<<< orphan*/  PARSE_OPT_NOCOMPLETE ; 
 int /*<<< orphan*/  PARSE_OPT_NONEG ; 
 int /*<<< orphan*/  apply_option_parse_directory ; 
 int /*<<< orphan*/  apply_option_parse_exclude ; 
 int /*<<< orphan*/  apply_option_parse_include ; 
 int /*<<< orphan*/  apply_option_parse_p ; 
 int /*<<< orphan*/  apply_option_parse_space_change ; 
 int /*<<< orphan*/  apply_option_parse_whitespace ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,struct option*,char const* const*,int /*<<< orphan*/ ) ; 

int apply_parse_options(int argc, const char **argv,
			struct apply_state *state,
			int *force_apply, int *options,
			const char * const *apply_usage)
{
	struct option builtin_apply_options[] = {
		{ OPTION_CALLBACK, 0, "exclude", state, N_("path"),
			N_("don't apply changes matching the given path"),
			PARSE_OPT_NONEG, apply_option_parse_exclude },
		{ OPTION_CALLBACK, 0, "include", state, N_("path"),
			N_("apply changes matching the given path"),
			PARSE_OPT_NONEG, apply_option_parse_include },
		{ OPTION_CALLBACK, 'p', NULL, state, N_("num"),
			N_("remove <num> leading slashes from traditional diff paths"),
			0, apply_option_parse_p },
		OPT_BOOL(0, "no-add", &state->no_add,
			N_("ignore additions made by the patch")),
		OPT_BOOL(0, "stat", &state->diffstat,
			N_("instead of applying the patch, output diffstat for the input")),
		OPT_NOOP_NOARG(0, "allow-binary-replacement"),
		OPT_NOOP_NOARG(0, "binary"),
		OPT_BOOL(0, "numstat", &state->numstat,
			N_("show number of added and deleted lines in decimal notation")),
		OPT_BOOL(0, "summary", &state->summary,
			N_("instead of applying the patch, output a summary for the input")),
		OPT_BOOL(0, "check", &state->check,
			N_("instead of applying the patch, see if the patch is applicable")),
		OPT_BOOL(0, "index", &state->check_index,
			N_("make sure the patch is applicable to the current index")),
		OPT_BOOL('N', "intent-to-add", &state->ita_only,
			N_("mark new files with `git add --intent-to-add`")),
		OPT_BOOL(0, "cached", &state->cached,
			N_("apply a patch without touching the working tree")),
		OPT_BOOL_F(0, "unsafe-paths", &state->unsafe_paths,
			   N_("accept a patch that touches outside the working area"),
			   PARSE_OPT_NOCOMPLETE),
		OPT_BOOL(0, "apply", force_apply,
			N_("also apply the patch (use with --stat/--summary/--check)")),
		OPT_BOOL('3', "3way", &state->threeway,
			 N_( "attempt three-way merge if a patch does not apply")),
		OPT_FILENAME(0, "build-fake-ancestor", &state->fake_ancestor,
			N_("build a temporary index based on embedded index information")),
		/* Think twice before adding "--nul" synonym to this */
		OPT_SET_INT('z', NULL, &state->line_termination,
			N_("paths are separated with NUL character"), '\0'),
		OPT_INTEGER('C', NULL, &state->p_context,
				N_("ensure at least <n> lines of context match")),
		{ OPTION_CALLBACK, 0, "whitespace", state, N_("action"),
			N_("detect new or modified lines that have whitespace errors"),
			0, apply_option_parse_whitespace },
		{ OPTION_CALLBACK, 0, "ignore-space-change", state, NULL,
			N_("ignore changes in whitespace when finding context"),
			PARSE_OPT_NOARG, apply_option_parse_space_change },
		{ OPTION_CALLBACK, 0, "ignore-whitespace", state, NULL,
			N_("ignore changes in whitespace when finding context"),
			PARSE_OPT_NOARG, apply_option_parse_space_change },
		OPT_BOOL('R', "reverse", &state->apply_in_reverse,
			N_("apply the patch in reverse")),
		OPT_BOOL(0, "unidiff-zero", &state->unidiff_zero,
			N_("don't expect at least one line of context")),
		OPT_BOOL(0, "reject", &state->apply_with_reject,
			N_("leave the rejected hunks in corresponding *.rej files")),
		OPT_BOOL(0, "allow-overlap", &state->allow_overlap,
			N_("allow overlapping hunks")),
		OPT__VERBOSE(&state->apply_verbosity, N_("be verbose")),
		OPT_BIT(0, "inaccurate-eof", options,
			N_("tolerate incorrectly detected missing new-line at the end of file"),
			APPLY_OPT_INACCURATE_EOF),
		OPT_BIT(0, "recount", options,
			N_("do not trust the line counts in the hunk headers"),
			APPLY_OPT_RECOUNT),
		{ OPTION_CALLBACK, 0, "directory", state, N_("root"),
			N_("prepend <root> to all filenames"),
			0, apply_option_parse_directory },
		OPT_END()
	};

	return parse_options(argc, argv, state->prefix, builtin_apply_options, apply_usage, 0);
}