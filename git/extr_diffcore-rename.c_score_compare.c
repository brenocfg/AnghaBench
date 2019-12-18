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
struct diff_score {scalar_t__ dst; scalar_t__ score; int name_score; } ;

/* Variables and functions */

__attribute__((used)) static int score_compare(const void *a_, const void *b_)
{
	const struct diff_score *a = a_, *b = b_;

	/* sink the unused ones to the bottom */
	if (a->dst < 0)
		return (0 <= b->dst);
	else if (b->dst < 0)
		return -1;

	if (a->score == b->score)
		return b->name_score - a->name_score;

	return b->score - a->score;
}