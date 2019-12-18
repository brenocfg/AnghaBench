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
struct TYPE_4__ {int /*<<< orphan*/ * argv; } ;
struct TYPE_3__ {int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED_RUN ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pack_refs ; 
 TYPE_2__ pack_refs_cmd ; 
 scalar_t__ prune_reflogs ; 
 TYPE_1__ reflog ; 
 scalar_t__ run_command_v_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_before_repack(void)
{
	/*
	 * We may be called twice, as both the pre- and
	 * post-daemonized phases will call us, but running these
	 * commands more than once is pointless and wasteful.
	 */
	static int done = 0;
	if (done++)
		return;

	if (pack_refs && run_command_v_opt(pack_refs_cmd.argv, RUN_GIT_CMD))
		die(FAILED_RUN, pack_refs_cmd.argv[0]);

	if (prune_reflogs && run_command_v_opt(reflog.argv, RUN_GIT_CMD))
		die(FAILED_RUN, reflog.argv[0]);
}