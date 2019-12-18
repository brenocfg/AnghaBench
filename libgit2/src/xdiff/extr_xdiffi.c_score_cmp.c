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
struct split_score {scalar_t__ effective_indent; int penalty; } ;

/* Variables and functions */
 int INDENT_WEIGHT ; 

__attribute__((used)) static int score_cmp(struct split_score *s1, struct split_score *s2)
{
	/* -1 if s1.effective_indent < s2->effective_indent, etc. */
	int cmp_indents = ((s1->effective_indent > s2->effective_indent) -
			   (s1->effective_indent < s2->effective_indent));

	return INDENT_WEIGHT * cmp_indents + (s1->penalty - s2->penalty);
}