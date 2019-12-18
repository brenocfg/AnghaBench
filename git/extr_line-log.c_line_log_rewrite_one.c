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
struct rev_info {int dummy; } ;
struct TYPE_3__ {int flags; } ;
struct commit {TYPE_2__* parents; TYPE_1__ object; } ;
typedef  enum rewrite_result { ____Placeholder_rewrite_result } rewrite_result ;
struct TYPE_4__ {struct commit* item; scalar_t__ next; } ;

/* Variables and functions */
 int TREESAME ; 
 int UNINTERESTING ; 
 int rewrite_one_noparents ; 
 int rewrite_one_ok ; 

__attribute__((used)) static enum rewrite_result line_log_rewrite_one(struct rev_info *rev, struct commit **pp)
{
	for (;;) {
		struct commit *p = *pp;
		if (p->parents && p->parents->next)
			return rewrite_one_ok;
		if (p->object.flags & UNINTERESTING)
			return rewrite_one_ok;
		if (!(p->object.flags & TREESAME))
			return rewrite_one_ok;
		if (!p->parents)
			return rewrite_one_noparents;
		*pp = p->parents->item;
	}
}