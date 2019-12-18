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
struct rev_info {int rev_input_given; } ;
struct all_refs_cb {unsigned int all_flags; int /*<<< orphan*/ * wt; struct rev_info* all_revs; } ;

/* Variables and functions */

__attribute__((used)) static void init_all_refs_cb(struct all_refs_cb *cb, struct rev_info *revs,
	unsigned flags)
{
	cb->all_revs = revs;
	cb->all_flags = flags;
	revs->rev_input_given = 1;
	cb->wt = NULL;
}