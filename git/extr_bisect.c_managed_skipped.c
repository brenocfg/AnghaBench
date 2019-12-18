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
struct commit_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 struct commit_list* filter_skipped (struct commit_list*,struct commit_list**,int /*<<< orphan*/ ,int*,int*) ; 
 struct commit_list* skip_away (struct commit_list*,int) ; 
 TYPE_1__ skipped_revs ; 

__attribute__((used)) static struct commit_list *managed_skipped(struct commit_list *list,
					   struct commit_list **tried)
{
	int count, skipped_first;

	*tried = NULL;

	if (!skipped_revs.nr)
		return list;

	list = filter_skipped(list, tried, 0, &count, &skipped_first);

	if (!skipped_first)
		return list;

	return skip_away(list, count);
}