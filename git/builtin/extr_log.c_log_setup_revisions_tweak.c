#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct setup_revision_opt {int dummy; } ;
struct TYPE_5__ {int follow_renames; scalar_t__ default_follow_renames; } ;
struct TYPE_6__ {scalar_t__ output_format; TYPE_2__ flags; } ;
struct TYPE_4__ {int nr; } ;
struct rev_info {scalar_t__ ignore_merges; scalar_t__ combine_merges; TYPE_3__ diffopt; TYPE_1__ prune_data; } ;

/* Variables and functions */
 scalar_t__ DIFF_FORMAT_PATCH ; 

__attribute__((used)) static void log_setup_revisions_tweak(struct rev_info *rev,
				      struct setup_revision_opt *opt)
{
	if (rev->diffopt.flags.default_follow_renames &&
	    rev->prune_data.nr == 1)
		rev->diffopt.flags.follow_renames = 1;

	/* Turn --cc/-c into -p --cc/-c when -p was not given */
	if (!rev->diffopt.output_format && rev->combine_merges)
		rev->diffopt.output_format = DIFF_FORMAT_PATCH;

	/* Turn -m on when --cc/-c was given */
	if (rev->combine_merges)
		rev->ignore_merges = 0;
}