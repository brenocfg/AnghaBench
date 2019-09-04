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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct child_process {char const** argv; int git_cmd; int no_stdin; int no_stderr; int no_stdout; char const* dir; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 char* read_gitfile (int /*<<< orphan*/ ) ; 
 scalar_t__ run_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int submodule_uses_gitfile(const char *path)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *argv[] = {
		"submodule",
		"foreach",
		"--quiet",
		"--recursive",
		"test -f .git",
		NULL,
	};
	struct strbuf buf = STRBUF_INIT;
	const char *git_dir;

	strbuf_addf(&buf, "%s/.git", path);
	git_dir = read_gitfile(buf.buf);
	if (!git_dir) {
		strbuf_release(&buf);
		return 0;
	}
	strbuf_release(&buf);

	/* Now test that all nested submodules use a gitfile too */
	cp.argv = argv;
	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.no_stderr = 1;
	cp.no_stdout = 1;
	cp.dir = path;
	if (run_command(&cp))
		return 0;

	return 1;
}