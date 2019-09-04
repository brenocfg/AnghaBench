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
struct object_id {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char const*,char*,int /*<<< orphan*/ *) ; 
 int bisect_clean_state () ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid_commit (char const*,struct object_id*) ; 
 int /*<<< orphan*/  git_path_bisect_head () ; 
 int /*<<< orphan*/  git_path_bisect_start () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ run_command_v_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 

__attribute__((used)) static int bisect_reset(const char *commit)
{
	struct strbuf branch = STRBUF_INIT;

	if (!commit) {
		if (strbuf_read_file(&branch, git_path_bisect_start(), 0) < 1) {
			printf(_("We are not bisecting.\n"));
			return 0;
		}
		strbuf_rtrim(&branch);
	} else {
		struct object_id oid;

		if (get_oid_commit(commit, &oid))
			return error(_("'%s' is not a valid commit"), commit);
		strbuf_addstr(&branch, commit);
	}

	if (!file_exists(git_path_bisect_head())) {
		struct argv_array argv = ARGV_ARRAY_INIT;

		argv_array_pushl(&argv, "checkout", branch.buf, "--", NULL);
		if (run_command_v_opt(argv.argv, RUN_GIT_CMD)) {
			strbuf_release(&branch);
			argv_array_clear(&argv);
			return error(_("could not check out original"
				       " HEAD '%s'. Try 'git bisect"
				       " reset <commit>'."), branch.buf);
		}
		argv_array_clear(&argv);
	}

	strbuf_release(&branch);
	return bisect_clean_state();
}