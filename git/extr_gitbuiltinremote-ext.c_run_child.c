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
struct child_process {int in; int out; int /*<<< orphan*/  args; scalar_t__ err; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int bidirectional_transfer_loop (int,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int finish_command (struct child_process*) ; 
 scalar_t__ git_req ; 
 int /*<<< orphan*/  git_req_vhost ; 
 int /*<<< orphan*/  parse_argv (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  send_git_request (int,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 

__attribute__((used)) static int run_child(const char *arg, const char *service)
{
	int r;
	struct child_process child = CHILD_PROCESS_INIT;

	child.in = -1;
	child.out = -1;
	child.err = 0;
	parse_argv(&child.args, arg, service);

	if (start_command(&child) < 0)
		die("Can't run specified command");

	if (git_req)
		send_git_request(child.in, service, git_req, git_req_vhost);

	r = bidirectional_transfer_loop(child.out, child.in);
	if (!r)
		r = finish_command(&child);
	else
		finish_command(&child);
	return r;
}