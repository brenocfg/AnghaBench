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
struct credential {int dummy; } ;
struct child_process {char const** argv; int use_shell; int in; int out; int no_stdout; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int credential_read (struct credential*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  credential_write (struct credential*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/ * xfdopen (int,char*) ; 

__attribute__((used)) static int run_credential_helper(struct credential *c,
				 const char *cmd,
				 int want_output)
{
	struct child_process helper = CHILD_PROCESS_INIT;
	const char *argv[] = { NULL, NULL };
	FILE *fp;

	argv[0] = cmd;
	helper.argv = argv;
	helper.use_shell = 1;
	helper.in = -1;
	if (want_output)
		helper.out = -1;
	else
		helper.no_stdout = 1;

	if (start_command(&helper) < 0)
		return -1;

	fp = xfdopen(helper.in, "w");
	sigchain_push(SIGPIPE, SIG_IGN);
	credential_write(c, fp);
	fclose(fp);
	sigchain_pop(SIGPIPE);

	if (want_output) {
		int r;
		fp = xfdopen(helper.out, "r");
		r = credential_read(c, fp);
		fclose(fp);
		if (r < 0) {
			finish_command(&helper);
			return -1;
		}
	}

	if (finish_command(&helper))
		return -1;
	return 0;
}