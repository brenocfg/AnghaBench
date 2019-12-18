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
struct setup_revision_opt {int dummy; } ;
struct TYPE_2__ {scalar_t__ output_format; } ;
struct rev_info {TYPE_1__ diffopt; scalar_t__ dense_combined_merges; } ;

/* Variables and functions */
 scalar_t__ DIFF_FORMAT_PATCH ; 
 scalar_t__ DIFF_FORMAT_RAW ; 

__attribute__((used)) static void diff_tree_tweak_rev(struct rev_info *rev, struct setup_revision_opt *opt)
{
	if (!rev->diffopt.output_format) {
		if (rev->dense_combined_merges)
			rev->diffopt.output_format = DIFF_FORMAT_PATCH;
		else
			rev->diffopt.output_format = DIFF_FORMAT_RAW;
	}
}