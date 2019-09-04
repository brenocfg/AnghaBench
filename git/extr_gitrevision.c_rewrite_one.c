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
struct rev_info {int /*<<< orphan*/  commits; } ;
struct prio_queue {int /*<<< orphan*/  member_0; } ;
struct commit {int dummy; } ;
typedef  enum rewrite_result { ____Placeholder_rewrite_result } rewrite_result ;

/* Variables and functions */
 int /*<<< orphan*/  clear_prio_queue (struct prio_queue*) ; 
 int /*<<< orphan*/  compare_commits_by_commit_date ; 
 int /*<<< orphan*/  merge_queue_into_list (struct prio_queue*,int /*<<< orphan*/ *) ; 
 int rewrite_one_1 (struct rev_info*,struct commit**,struct prio_queue*) ; 

__attribute__((used)) static enum rewrite_result rewrite_one(struct rev_info *revs, struct commit **pp)
{
	struct prio_queue queue = { compare_commits_by_commit_date };
	enum rewrite_result ret = rewrite_one_1(revs, pp, &queue);
	merge_queue_into_list(&queue, &revs->commits);
	clear_prio_queue(&queue);
	return ret;
}