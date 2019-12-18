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
struct diff_options {int output_format; } ;
struct rev_info {struct diff_options diffopt; } ;
struct combine_diff_path {int dummy; } ;

/* Variables and functions */
 int DIFF_FORMAT_NAME ; 
 int DIFF_FORMAT_NAME_STATUS ; 
 int DIFF_FORMAT_PATCH ; 
 int DIFF_FORMAT_RAW ; 
 int /*<<< orphan*/  show_patch_diff (struct combine_diff_path*,int,int,int,struct rev_info*) ; 
 int /*<<< orphan*/  show_raw_diff (struct combine_diff_path*,int,struct rev_info*) ; 

void show_combined_diff(struct combine_diff_path *p,
		       int num_parent,
		       int dense,
		       struct rev_info *rev)
{
	struct diff_options *opt = &rev->diffopt;

	if (opt->output_format & (DIFF_FORMAT_RAW |
				  DIFF_FORMAT_NAME |
				  DIFF_FORMAT_NAME_STATUS))
		show_raw_diff(p, num_parent, rev);
	else if (opt->output_format & DIFF_FORMAT_PATCH)
		show_patch_diff(p, num_parent, dense, 1, rev);
}