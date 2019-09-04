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
struct strbuf {char* buf; scalar_t__ len; } ;
struct child_process {int git_cmd; int no_stdin; int out; char const* dir; int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char*) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 unsigned int DIRTY_SUBMODULE_MODIFIED ; 
 unsigned int DIRTY_SUBMODULE_UNTRACKED ; 
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 scalar_t__ is_directory (char const*) ; 
 int /*<<< orphan*/  is_git_directory (char const*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 char* read_gitfile (char*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 scalar_t__ strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/ * xfdopen (int,char*) ; 

unsigned is_submodule_modified(const char *path, int ignore_untracked)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	FILE *fp;
	unsigned dirty_submodule = 0;
	const char *git_dir;
	int ignore_cp_exit_code = 0;

	strbuf_addf(&buf, "%s/.git", path);
	git_dir = read_gitfile(buf.buf);
	if (!git_dir)
		git_dir = buf.buf;
	if (!is_git_directory(git_dir)) {
		if (is_directory(git_dir))
			die(_("'%s' not recognized as a git repository"), git_dir);
		strbuf_release(&buf);
		/* The submodule is not checked out, so it is not modified */
		return 0;
	}
	strbuf_reset(&buf);

	argv_array_pushl(&cp.args, "status", "--porcelain=2", NULL);
	if (ignore_untracked)
		argv_array_push(&cp.args, "-uno");

	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.dir = path;
	if (start_command(&cp))
		die("Could not run 'git status --porcelain=2' in submodule %s", path);

	fp = xfdopen(cp.out, "r");
	while (strbuf_getwholeline(&buf, fp, '\n') != EOF) {
		/* regular untracked files */
		if (buf.buf[0] == '?')
			dirty_submodule |= DIRTY_SUBMODULE_UNTRACKED;

		if (buf.buf[0] == 'u' ||
		    buf.buf[0] == '1' ||
		    buf.buf[0] == '2') {
			/* T = line type, XY = status, SSSS = submodule state */
			if (buf.len < strlen("T XY SSSS"))
				BUG("invalid status --porcelain=2 line %s",
				    buf.buf);

			if (buf.buf[5] == 'S' && buf.buf[8] == 'U')
				/* nested untracked file */
				dirty_submodule |= DIRTY_SUBMODULE_UNTRACKED;

			if (buf.buf[0] == 'u' ||
			    buf.buf[0] == '2' ||
			    memcmp(buf.buf + 5, "S..U", 4))
				/* other change */
				dirty_submodule |= DIRTY_SUBMODULE_MODIFIED;
		}

		if ((dirty_submodule & DIRTY_SUBMODULE_MODIFIED) &&
		    ((dirty_submodule & DIRTY_SUBMODULE_UNTRACKED) ||
		     ignore_untracked)) {
			/*
			 * We're not interested in any further information from
			 * the child any more, neither output nor its exit code.
			 */
			ignore_cp_exit_code = 1;
			break;
		}
	}
	fclose(fp);

	if (finish_command(&cp) && !ignore_cp_exit_code)
		die("'git status --porcelain=2' failed in submodule %s", path);

	strbuf_release(&buf);
	return dirty_submodule;
}