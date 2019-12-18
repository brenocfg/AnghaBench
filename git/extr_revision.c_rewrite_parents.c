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
struct rev_info {int dummy; } ;
struct commit_list {struct commit_list* next; int /*<<< orphan*/  item; } ;
struct commit {struct commit_list* parents; } ;
typedef  int (* rewrite_parent_fn_t ) (struct rev_info*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  remove_duplicate_parents (struct rev_info*,struct commit*) ; 
#define  rewrite_one_error 130 
#define  rewrite_one_noparents 129 
#define  rewrite_one_ok 128 

int rewrite_parents(struct rev_info *revs, struct commit *commit,
	rewrite_parent_fn_t rewrite_parent)
{
	struct commit_list **pp = &commit->parents;
	while (*pp) {
		struct commit_list *parent = *pp;
		switch (rewrite_parent(revs, &parent->item)) {
		case rewrite_one_ok:
			break;
		case rewrite_one_noparents:
			*pp = parent->next;
			continue;
		case rewrite_one_error:
			return -1;
		}
		pp = &parent->next;
	}
	remove_duplicate_parents(revs, commit);
	return 0;
}