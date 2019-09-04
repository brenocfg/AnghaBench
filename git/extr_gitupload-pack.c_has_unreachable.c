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
struct object_array {int dummy; } ;
struct child_process {int out; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ do_reachable_revlist (struct child_process*,struct object_array*,int /*<<< orphan*/ *) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int read_in_full (int,char*,int) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int has_unreachable(struct object_array *src)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	char buf[1];
	int i;

	if (do_reachable_revlist(&cmd, src, NULL) < 0)
		return 1;

	/*
	 * The commits out of the rev-list are not ancestors of
	 * our ref.
	 */
	i = read_in_full(cmd.out, buf, 1);
	if (i)
		goto error;
	close(cmd.out);
	cmd.out = -1;

	/*
	 * rev-list may have died by encountering a bad commit
	 * in the history, in which case we do want to bail out
	 * even when it showed no commit.
	 */
	if (finish_command(&cmd))
		goto error;

	/* All the non-tip ones are ancestors of what we advertised */
	return 0;

error:
	sigchain_pop(SIGPIPE);
	if (cmd.out >= 0)
		close(cmd.out);
	return 1;
}