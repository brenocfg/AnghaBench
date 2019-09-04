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
struct child_process {int git_cmd; int err; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  copy_to_log (int) ; 
 int finish_command (struct child_process*) ; 
 scalar_t__ start_command (struct child_process*) ; 

__attribute__((used)) static int run_service_command(struct child_process *cld)
{
	argv_array_push(&cld->args, ".");
	cld->git_cmd = 1;
	cld->err = -1;
	if (start_command(cld))
		return -1;

	close(0);
	close(1);

	copy_to_log(cld->err);

	return finish_command(cld);
}