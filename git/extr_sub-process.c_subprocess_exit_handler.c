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
struct child_process {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_command (struct child_process*) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void subprocess_exit_handler(struct child_process *process)
{
	sigchain_push(SIGPIPE, SIG_IGN);
	/* Closing the pipe signals the subprocess to initiate a shutdown. */
	close(process->in);
	close(process->out);
	sigchain_pop(SIGPIPE);
	/* Finish command will wait until the shutdown is complete. */
	finish_command(process);
}