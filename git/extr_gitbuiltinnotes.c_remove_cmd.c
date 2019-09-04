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
struct strbuf {char const* buf; } ;
struct option {int dummy; } ;
struct notes_tree {int dummy; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  IGNORE_MISSING ; 
 int /*<<< orphan*/  NOTES_INIT_WRITABLE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BIT (int /*<<< orphan*/ ,char*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  commit_notes (int /*<<< orphan*/ ,struct notes_tree*,char*) ; 
 int /*<<< orphan*/  free_notes (struct notes_tree*) ; 
 int /*<<< orphan*/  git_notes_remove_usage ; 
 struct notes_tree* init_notes_check (char*,int /*<<< orphan*/ ) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int remove_one_note (struct notes_tree*,char const*,unsigned int) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int remove_cmd(int argc, const char **argv, const char *prefix)
{
	unsigned flag = 0;
	int from_stdin = 0;
	struct option options[] = {
		OPT_BIT(0, "ignore-missing", &flag,
			N_("attempt to remove non-existent note is not an error"),
			IGNORE_MISSING),
		OPT_BOOL(0, "stdin", &from_stdin,
			    N_("read object names from the standard input")),
		OPT_END()
	};
	struct notes_tree *t;
	int retval = 0;

	argc = parse_options(argc, argv, prefix, options,
			     git_notes_remove_usage, 0);

	t = init_notes_check("remove", NOTES_INIT_WRITABLE);

	if (!argc && !from_stdin) {
		retval = remove_one_note(t, "HEAD", flag);
	} else {
		while (*argv) {
			retval |= remove_one_note(t, *argv, flag);
			argv++;
		}
	}
	if (from_stdin) {
		struct strbuf sb = STRBUF_INIT;
		while (strbuf_getwholeline(&sb, stdin, '\n') != EOF) {
			strbuf_rtrim(&sb);
			retval |= remove_one_note(t, sb.buf, flag);
		}
		strbuf_release(&sb);
	}
	if (!retval)
		commit_notes(the_repository, t,
			     "Notes removed by 'git notes remove'");
	free_notes(t);
	return retval;
}