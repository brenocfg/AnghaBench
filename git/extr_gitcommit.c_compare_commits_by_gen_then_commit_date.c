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
struct commit {scalar_t__ generation; scalar_t__ date; } ;

/* Variables and functions */

int compare_commits_by_gen_then_commit_date(const void *a_, const void *b_, void *unused)
{
	const struct commit *a = a_, *b = b_;

	/* newer commits first */
	if (a->generation < b->generation)
		return 1;
	else if (a->generation > b->generation)
		return -1;

	/* use date as a heuristic when generations are equal */
	if (a->date < b->date)
		return 1;
	else if (a->date > b->date)
		return -1;
	return 0;
}