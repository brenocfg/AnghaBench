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
struct commit_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_list_compare_by_date ; 
 int /*<<< orphan*/  commit_list_get_next ; 
 int /*<<< orphan*/  commit_list_set_next ; 
 struct commit_list* llist_mergesort (struct commit_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void commit_list_sort_by_date(struct commit_list **list)
{
	*list = llist_mergesort(*list, commit_list_get_next, commit_list_set_next,
				commit_list_compare_by_date);
}