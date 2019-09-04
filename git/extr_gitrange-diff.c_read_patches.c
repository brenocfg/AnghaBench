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
struct string_list {int dummy; } ;
struct strbuf {char* buf; scalar_t__ len; } ;
struct patch_util {int matching; int /*<<< orphan*/  diffsize; scalar_t__ diff_offset; int /*<<< orphan*/  oid; } ;
struct child_process {int out; int no_stdin; int git_cmd; int /*<<< orphan*/  args; } ;
struct TYPE_2__ {struct patch_util* util; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (struct patch_util*) ; 
 scalar_t__ get_oid (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 scalar_t__ start_command (struct child_process*) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 TYPE_1__* string_list_append (struct string_list*,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 struct patch_util* xcalloc (int,int) ; 

__attribute__((used)) static int read_patches(const char *range, struct string_list *list)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	FILE *in;
	struct strbuf buf = STRBUF_INIT, line = STRBUF_INIT;
	struct patch_util *util = NULL;
	int in_header = 1;

	argv_array_pushl(&cp.args, "log", "--no-color", "-p", "--no-merges",
			"--reverse", "--date-order", "--decorate=no",
			/*
			 * Choose indicators that are not used anywhere
			 * else in diffs, but still look reasonable
			 * (e.g. will not be confusing when debugging)
			 */
			"--output-indicator-new=>",
			"--output-indicator-old=<",
			"--output-indicator-context=#",
			"--no-abbrev-commit", range,
			NULL);
	cp.out = -1;
	cp.no_stdin = 1;
	cp.git_cmd = 1;

	if (start_command(&cp))
		return error_errno(_("could not start `log`"));
	in = fdopen(cp.out, "r");
	if (!in) {
		error_errno(_("could not read `log` output"));
		finish_command(&cp);
		return -1;
	}

	while (strbuf_getline(&line, in) != EOF) {
		const char *p;

		if (skip_prefix(line.buf, "commit ", &p)) {
			if (util) {
				string_list_append(list, buf.buf)->util = util;
				strbuf_reset(&buf);
			}
			util = xcalloc(sizeof(*util), 1);
			if (get_oid(p, &util->oid)) {
				error(_("could not parse commit '%s'"), p);
				free(util);
				string_list_clear(list, 1);
				strbuf_release(&buf);
				strbuf_release(&line);
				fclose(in);
				finish_command(&cp);
				return -1;
			}
			util->matching = -1;
			in_header = 1;
			continue;
		}

		if (starts_with(line.buf, "diff --git")) {
			in_header = 0;
			strbuf_addch(&buf, '\n');
			if (!util->diff_offset)
				util->diff_offset = buf.len;
			strbuf_addch(&buf, ' ');
			strbuf_addbuf(&buf, &line);
		} else if (in_header) {
			if (starts_with(line.buf, "Author: ")) {
				strbuf_addbuf(&buf, &line);
				strbuf_addstr(&buf, "\n\n");
			} else if (starts_with(line.buf, "    ")) {
				strbuf_rtrim(&line);
				strbuf_addbuf(&buf, &line);
				strbuf_addch(&buf, '\n');
			}
			continue;
		} else if (starts_with(line.buf, "@@ "))
			strbuf_addstr(&buf, "@@");
		else if (!line.buf[0] || starts_with(line.buf, "index "))
			/*
			 * A completely blank (not ' \n', which is context)
			 * line is not valid in a diff.  We skip it
			 * silently, because this neatly handles the blank
			 * separator line between commits in git-log
			 * output.
			 *
			 * We also want to ignore the diff's `index` lines
			 * because they contain exact blob hashes in which
			 * we are not interested.
			 */
			continue;
		else if (line.buf[0] == '>') {
			strbuf_addch(&buf, '+');
			strbuf_add(&buf, line.buf + 1, line.len - 1);
		} else if (line.buf[0] == '<') {
			strbuf_addch(&buf, '-');
			strbuf_add(&buf, line.buf + 1, line.len - 1);
		} else if (line.buf[0] == '#') {
			strbuf_addch(&buf, ' ');
			strbuf_add(&buf, line.buf + 1, line.len - 1);
		} else {
			strbuf_addch(&buf, ' ');
			strbuf_addbuf(&buf, &line);
		}

		strbuf_addch(&buf, '\n');
		util->diffsize++;
	}
	fclose(in);
	strbuf_release(&line);

	if (util)
		string_list_append(list, buf.buf)->util = util;
	strbuf_release(&buf);

	if (finish_command(&cp))
		return -1;

	return 0;
}