#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct replay_opts {scalar_t__ action; TYPE_1__* revs; } ;
struct TYPE_2__ {int reverse; int /*<<< orphan*/  no_walk; } ;

/* Variables and functions */
 scalar_t__ REPLAY_PICK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_revision_walk (TYPE_1__*) ; 

__attribute__((used)) static int prepare_revs(struct replay_opts *opts)
{
	/*
	 * picking (but not reverting) ranges (but not individual revisions)
	 * should be done in reverse
	 */
	if (opts->action == REPLAY_PICK && !opts->revs->no_walk)
		opts->revs->reverse ^= 1;

	if (prepare_revision_walk(opts->revs))
		return error(_("revision walk setup failed"));

	return 0;
}