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
struct child_process {int stdout_to_stderr; char* trace2_hook_name; int /*<<< orphan*/  in; int /*<<< orphan*/  args; } ;
struct am_state {int dummy; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  am_path (struct am_state const*,char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 char* find_hook (char*) ; 
 int run_command (struct child_process*) ; 
 int /*<<< orphan*/  xopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_post_rewrite_hook(const struct am_state *state)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *hook = find_hook("post-rewrite");
	int ret;

	if (!hook)
		return 0;

	argv_array_push(&cp.args, hook);
	argv_array_push(&cp.args, "rebase");

	cp.in = xopen(am_path(state, "rewritten"), O_RDONLY);
	cp.stdout_to_stderr = 1;
	cp.trace2_hook_name = "post-rewrite";

	ret = run_command(&cp);

	close(cp.in);
	return ret;
}