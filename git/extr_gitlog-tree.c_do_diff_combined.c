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
struct rev_info {int /*<<< orphan*/  loginfo; int /*<<< orphan*/  dense_combined_merges; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_tree_combined_merge (struct commit*,int /*<<< orphan*/ ,struct rev_info*) ; 

__attribute__((used)) static int do_diff_combined(struct rev_info *opt, struct commit *commit)
{
	diff_tree_combined_merge(commit, opt->dense_combined_merges, opt);
	return !opt->loginfo;
}