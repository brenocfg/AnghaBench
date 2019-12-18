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
struct rev_info {struct commit_list* commits; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_child (struct rev_info*,struct commit*,struct commit*) ; 

__attribute__((used)) static void set_children(struct rev_info *revs)
{
	struct commit_list *l;
	for (l = revs->commits; l; l = l->next) {
		struct commit *commit = l->item;
		struct commit_list *p;

		for (p = commit->parents; p; p = p->next)
			add_child(revs, p->item, commit);
	}
}