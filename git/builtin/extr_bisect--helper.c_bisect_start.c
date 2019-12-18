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
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {char const* buf; } ;
struct object_id {int dummy; } ;
struct bisect_terms {char const* term_good; char const* term_bad; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  UPDATE_REFS_MSG_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char const*,char*,int /*<<< orphan*/ *) ; 
 int bisect_append_log_quoted (char const**) ; 
 scalar_t__ bisect_clean_state () ; 
 scalar_t__ bisect_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bisect_terms*,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  git_path_bisect_names () ; 
 int /*<<< orphan*/  git_path_bisect_start () ; 
 int /*<<< orphan*/  git_path_head_name () ; 
 scalar_t__ is_bare_repository () ; 
 int /*<<< orphan*/  is_empty_or_missing_file (int /*<<< orphan*/ ) ; 
 char const* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  one_of (char const*,char*,char*,int /*<<< orphan*/ *) ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 scalar_t__ run_command_v_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  sq_quote_argv (struct strbuf*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ update_ref (int /*<<< orphan*/ *,char*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ write_terms (char const*,char const*) ; 
 void* xstrdup (char const*) ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static int bisect_start(struct bisect_terms *terms, int no_checkout,
			const char **argv, int argc)
{
	int i, has_double_dash = 0, must_write_terms = 0, bad_seen = 0;
	int flags, pathspec_pos, retval = 0;
	struct string_list revs = STRING_LIST_INIT_DUP;
	struct string_list states = STRING_LIST_INIT_DUP;
	struct strbuf start_head = STRBUF_INIT;
	struct strbuf bisect_names = STRBUF_INIT;
	struct object_id head_oid;
	struct object_id oid;
	const char *head;

	if (is_bare_repository())
		no_checkout = 1;

	/*
	 * Check for one bad and then some good revisions
	 */
	for (i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "--")) {
			has_double_dash = 1;
			break;
		}
	}

	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(argv[i], "--")) {
			break;
		} else if (!strcmp(arg, "--no-checkout")) {
			no_checkout = 1;
		} else if (!strcmp(arg, "--term-good") ||
			 !strcmp(arg, "--term-old")) {
			must_write_terms = 1;
			free((void *) terms->term_good);
			terms->term_good = xstrdup(argv[++i]);
		} else if (skip_prefix(arg, "--term-good=", &arg) ||
			   skip_prefix(arg, "--term-old=", &arg)) {
			must_write_terms = 1;
			free((void *) terms->term_good);
			terms->term_good = xstrdup(arg);
		} else if (!strcmp(arg, "--term-bad") ||
			 !strcmp(arg, "--term-new")) {
			must_write_terms = 1;
			free((void *) terms->term_bad);
			terms->term_bad = xstrdup(argv[++i]);
		} else if (skip_prefix(arg, "--term-bad=", &arg) ||
			   skip_prefix(arg, "--term-new=", &arg)) {
			must_write_terms = 1;
			free((void *) terms->term_bad);
			terms->term_bad = xstrdup(arg);
		} else if (starts_with(arg, "--") &&
			 !one_of(arg, "--term-good", "--term-bad", NULL)) {
			return error(_("unrecognized option: '%s'"), arg);
		} else {
			char *commit_id = xstrfmt("%s^{commit}", arg);
			if (get_oid(commit_id, &oid) && has_double_dash)
				die(_("'%s' does not appear to be a valid "
				      "revision"), arg);

			string_list_append(&revs, oid_to_hex(&oid));
			free(commit_id);
		}
	}
	pathspec_pos = i;

	/*
	 * The user ran "git bisect start <sha1> <sha1>", hence did not
	 * explicitly specify the terms, but we are already starting to
	 * set references named with the default terms, and won't be able
	 * to change afterwards.
	 */
	if (revs.nr)
		must_write_terms = 1;
	for (i = 0; i < revs.nr; i++) {
		if (bad_seen) {
			string_list_append(&states, terms->term_good);
		} else {
			bad_seen = 1;
			string_list_append(&states, terms->term_bad);
		}
	}

	/*
	 * Verify HEAD
	 */
	head = resolve_ref_unsafe("HEAD", 0, &head_oid, &flags);
	if (!head)
		if (get_oid("HEAD", &head_oid))
			return error(_("bad HEAD - I need a HEAD"));

	/*
	 * Check if we are bisecting
	 */
	if (!is_empty_or_missing_file(git_path_bisect_start())) {
		/* Reset to the rev from where we started */
		strbuf_read_file(&start_head, git_path_bisect_start(), 0);
		strbuf_trim(&start_head);
		if (!no_checkout) {
			struct argv_array argv = ARGV_ARRAY_INIT;

			argv_array_pushl(&argv, "checkout", start_head.buf,
					 "--", NULL);
			if (run_command_v_opt(argv.argv, RUN_GIT_CMD)) {
				retval = error(_("checking out '%s' failed."
						 " Try 'git bisect start "
						 "<valid-branch>'."),
					       start_head.buf);
				goto finish;
			}
		}
	} else {
		/* Get the rev from where we start. */
		if (!get_oid(head, &head_oid) &&
		    !starts_with(head, "refs/heads/")) {
			strbuf_reset(&start_head);
			strbuf_addstr(&start_head, oid_to_hex(&head_oid));
		} else if (!get_oid(head, &head_oid) &&
			   skip_prefix(head, "refs/heads/", &head)) {
			/*
			 * This error message should only be triggered by
			 * cogito usage, and cogito users should understand
			 * it relates to cg-seek.
			 */
			if (!is_empty_or_missing_file(git_path_head_name()))
				return error(_("won't bisect on cg-seek'ed tree"));
			strbuf_addstr(&start_head, head);
		} else {
			return error(_("bad HEAD - strange symbolic ref"));
		}
	}

	/*
	 * Get rid of any old bisect state.
	 */
	if (bisect_clean_state())
		return -1;

	/*
	 * In case of mistaken revs or checkout error, or signals received,
	 * "bisect_auto_next" below may exit or misbehave.
	 * We have to trap this to be able to clean up using
	 * "bisect_clean_state".
	 */

	/*
	 * Write new start state
	 */
	write_file(git_path_bisect_start(), "%s\n", start_head.buf);

	if (no_checkout) {
		if (get_oid(start_head.buf, &oid) < 0) {
			retval = error(_("invalid ref: '%s'"), start_head.buf);
			goto finish;
		}
		if (update_ref(NULL, "BISECT_HEAD", &oid, NULL, 0,
			       UPDATE_REFS_MSG_ON_ERR)) {
			retval = -1;
			goto finish;
		}
	}

	if (pathspec_pos < argc - 1)
		sq_quote_argv(&bisect_names, argv + pathspec_pos);
	write_file(git_path_bisect_names(), "%s\n", bisect_names.buf);

	for (i = 0; i < states.nr; i++)
		if (bisect_write(states.items[i].string,
				 revs.items[i].string, terms, 1)) {
			retval = -1;
			goto finish;
		}

	if (must_write_terms && write_terms(terms->term_bad,
					    terms->term_good)) {
		retval = -1;
		goto finish;
	}

	retval = bisect_append_log_quoted(argv);
	if (retval)
		retval = -1;

finish:
	string_list_clear(&revs, 0);
	string_list_clear(&states, 0);
	strbuf_release(&start_head);
	strbuf_release(&bisect_names);
	return retval;
}