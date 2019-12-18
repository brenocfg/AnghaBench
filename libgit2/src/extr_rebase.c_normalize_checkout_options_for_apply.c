#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  checkout_options; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ onto_name; TYPE_1__ options; } ;
typedef  TYPE_2__ git_rebase ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_9__ {char* ancestor_label; scalar_t__ their_label; scalar_t__ our_label; } ;
typedef  TYPE_3__ git_checkout_options ;

/* Variables and functions */
 scalar_t__ GIT_REBASE_TYPE_MERGE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ git_commit_summary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void normalize_checkout_options_for_apply(
	git_checkout_options *checkout_opts,
	git_rebase *rebase,
	git_commit *current_commit)
{
	memcpy(checkout_opts, &rebase->options.checkout_options, sizeof(git_checkout_options));

	if (!checkout_opts->ancestor_label)
		checkout_opts->ancestor_label = "ancestor";

	if (rebase->type == GIT_REBASE_TYPE_MERGE) {
		if (!checkout_opts->our_label)
			checkout_opts->our_label = rebase->onto_name;

		if (!checkout_opts->their_label)
			checkout_opts->their_label = git_commit_summary(current_commit);
	} else {
		abort();
	}
}