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
struct setup_revision_opt {char const* def; } ;
struct TYPE_4__ {int quick; int exit_with_status; scalar_t__ has_changes; } ;
struct TYPE_3__ {int ita_invisible_in_index; TYPE_2__ flags; } ;
struct rev_info {TYPE_1__ diffopt; int /*<<< orphan*/  pending; } ;
struct repository {int dummy; } ;
struct diff_flags {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  diff_flags_or (TYPE_2__*,struct diff_flags const*) ; 
 int /*<<< orphan*/  memset (struct setup_revision_opt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  object_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_diff_index (struct rev_info*,int) ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rev_info*,struct setup_revision_opt*) ; 

int index_differs_from(struct repository *r,
		       const char *def, const struct diff_flags *flags,
		       int ita_invisible_in_index)
{
	struct rev_info rev;
	struct setup_revision_opt opt;

	repo_init_revisions(r, &rev, NULL);
	memset(&opt, 0, sizeof(opt));
	opt.def = def;
	setup_revisions(0, NULL, &rev, &opt);
	rev.diffopt.flags.quick = 1;
	rev.diffopt.flags.exit_with_status = 1;
	if (flags)
		diff_flags_or(&rev.diffopt.flags, flags);
	rev.diffopt.ita_invisible_in_index = ita_invisible_in_index;
	run_diff_index(&rev, 1);
	object_array_clear(&rev.pending);
	return (rev.diffopt.flags.has_changes != 0);
}