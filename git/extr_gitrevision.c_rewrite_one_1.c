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
struct rev_info {int /*<<< orphan*/  limited; } ;
struct prio_queue {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct commit {int /*<<< orphan*/  parents; TYPE_1__ object; } ;
typedef  enum rewrite_result { ____Placeholder_rewrite_result } rewrite_result ;

/* Variables and functions */
 int TREESAME ; 
 int UNINTERESTING ; 
 struct commit* one_relevant_parent (struct rev_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ process_parents (struct rev_info*,struct commit*,int /*<<< orphan*/ *,struct prio_queue*) ; 
 int rewrite_one_error ; 
 int rewrite_one_noparents ; 
 int rewrite_one_ok ; 

__attribute__((used)) static enum rewrite_result rewrite_one_1(struct rev_info *revs,
					 struct commit **pp,
					 struct prio_queue *queue)
{
	for (;;) {
		struct commit *p = *pp;
		if (!revs->limited)
			if (process_parents(revs, p, NULL, queue) < 0)
				return rewrite_one_error;
		if (p->object.flags & UNINTERESTING)
			return rewrite_one_ok;
		if (!(p->object.flags & TREESAME))
			return rewrite_one_ok;
		if (!p->parents)
			return rewrite_one_noparents;
		if ((p = one_relevant_parent(revs, p->parents)) == NULL)
			return rewrite_one_ok;
		*pp = p;
	}
}