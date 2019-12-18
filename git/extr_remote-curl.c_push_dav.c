#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;
struct TYPE_4__ {int verbosity; scalar_t__ dry_run; } ;
struct TYPE_3__ {char const* buf; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 TYPE_2__ options ; 
 scalar_t__ run_command (struct child_process*) ; 
 TYPE_1__ url ; 

__attribute__((used)) static int push_dav(int nr_spec, const char **specs)
{
	struct child_process child = CHILD_PROCESS_INIT;
	size_t i;

	child.git_cmd = 1;
	argv_array_push(&child.args, "http-push");
	argv_array_push(&child.args, "--helper-status");
	if (options.dry_run)
		argv_array_push(&child.args, "--dry-run");
	if (options.verbosity > 1)
		argv_array_push(&child.args, "--verbose");
	argv_array_push(&child.args, url.buf);
	for (i = 0; i < nr_spec; i++)
		argv_array_push(&child.args, specs[i]);

	if (run_command(&child))
		die(_("git-http-push failed"));
	return 0;
}