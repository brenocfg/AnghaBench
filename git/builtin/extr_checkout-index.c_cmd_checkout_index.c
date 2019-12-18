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
struct strbuf {char* buf; } ;
struct option {char* member_2; char* member_4; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct lock_file {int dummy; } ;
typedef  scalar_t__ (* strbuf_getline_fn ) (struct strbuf*,int /*<<< orphan*/ ) ;
struct TYPE_2__ {char* base_dir; int force; int quiet; int not_new; int refresh_cache; int /*<<< orphan*/ * istate; void* base_dir_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_LOCK ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_CALLBACK ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__FORCE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__QUIET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_NONEG ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  builtin_checkout_index_usage ; 
 int /*<<< orphan*/  checkout_all (char const*,int) ; 
 int /*<<< orphan*/  checkout_file (char*,char const*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_lock_file_locked (struct lock_file*) ; 
 int nul_term_line ; 
 int /*<<< orphan*/  option_parse_stage ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* prefix_path (char const*,int,char const*) ; 
 scalar_t__ read_cache () ; 
 TYPE_1__ state ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_getline_nul (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strlen (char const*) ; 
 int /*<<< orphan*/  the_index ; 
 int to_tempfile ; 
 scalar_t__ unquote_c_style (struct strbuf*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int /*<<< orphan*/ ) ; 

int cmd_checkout_index(int argc, const char **argv, const char *prefix)
{
	int i;
	struct lock_file lock_file = LOCK_INIT;
	int all = 0;
	int read_from_stdin = 0;
	int prefix_length;
	int force = 0, quiet = 0, not_new = 0;
	int index_opt = 0;
	struct option builtin_checkout_index_options[] = {
		OPT_BOOL('a', "all", &all,
			N_("check out all files in the index")),
		OPT__FORCE(&force, N_("force overwrite of existing files"), 0),
		OPT__QUIET(&quiet,
			N_("no warning for existing files and files not in index")),
		OPT_BOOL('n', "no-create", &not_new,
			N_("don't checkout new files")),
		OPT_BOOL('u', "index", &index_opt,
			 N_("update stat information in the index file")),
		OPT_BOOL('z', NULL, &nul_term_line,
			N_("paths are separated with NUL character")),
		OPT_BOOL(0, "stdin", &read_from_stdin,
			N_("read list of paths from the standard input")),
		OPT_BOOL(0, "temp", &to_tempfile,
			N_("write the content to temporary files")),
		OPT_STRING(0, "prefix", &state.base_dir, N_("string"),
			N_("when creating files, prepend <string>")),
		{ OPTION_CALLBACK, 0, "stage", NULL, "(1|2|3|all)",
			N_("copy out the files from named stage"),
			PARSE_OPT_NONEG, option_parse_stage },
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_checkout_index_usage,
				   builtin_checkout_index_options);
	git_config(git_default_config, NULL);
	prefix_length = prefix ? strlen(prefix) : 0;

	if (read_cache() < 0) {
		die("invalid cache");
	}

	argc = parse_options(argc, argv, prefix, builtin_checkout_index_options,
			builtin_checkout_index_usage, 0);
	state.istate = &the_index;
	state.force = force;
	state.quiet = quiet;
	state.not_new = not_new;

	if (!state.base_dir)
		state.base_dir = "";
	state.base_dir_len = strlen(state.base_dir);

	/*
	 * when --prefix is specified we do not want to update cache.
	 */
	if (index_opt && !state.base_dir_len && !to_tempfile) {
		state.refresh_cache = 1;
		state.istate = &the_index;
		hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
	}

	/* Check out named files first */
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		char *p;

		if (all)
			die("git checkout-index: don't mix '--all' and explicit filenames");
		if (read_from_stdin)
			die("git checkout-index: don't mix '--stdin' and explicit filenames");
		p = prefix_path(prefix, prefix_length, arg);
		checkout_file(p, prefix);
		free(p);
	}

	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT;
		struct strbuf unquoted = STRBUF_INIT;
		strbuf_getline_fn getline_fn;

		if (all)
			die("git checkout-index: don't mix '--all' and '--stdin'");

		getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
		while (getline_fn(&buf, stdin) != EOF) {
			char *p;
			if (!nul_term_line && buf.buf[0] == '"') {
				strbuf_reset(&unquoted);
				if (unquote_c_style(&unquoted, buf.buf, NULL))
					die("line is badly quoted");
				strbuf_swap(&buf, &unquoted);
			}
			p = prefix_path(prefix, prefix_length, buf.buf);
			checkout_file(p, prefix);
			free(p);
		}
		strbuf_release(&unquoted);
		strbuf_release(&buf);
	}

	if (all)
		checkout_all(prefix, prefix_length);

	if (is_lock_file_locked(&lock_file) &&
	    write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
		die("Unable to write new index file");
	return 0;
}