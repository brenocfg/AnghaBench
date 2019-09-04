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
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ capture_command (struct child_process*,struct strbuf*,int) ; 
 int git_env_bool (char*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int use_builtin_stash(void)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf out = STRBUF_INIT;
	int ret, env = git_env_bool("GIT_TEST_STASH_USE_BUILTIN", -1);

	if (env != -1)
		return env;

	argv_array_pushl(&cp.args,
			 "config", "--bool", "stash.usebuiltin", NULL);
	cp.git_cmd = 1;
	if (capture_command(&cp, &out, 6)) {
		strbuf_release(&out);
		return 1;
	}

	strbuf_trim(&out);
	ret = !strcmp("true", out.buf);
	strbuf_release(&out);
	return ret;
}