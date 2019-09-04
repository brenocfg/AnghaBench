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
struct refspec_item {scalar_t__ matching; scalar_t__ pattern; } ;
struct refspec {int nr; struct refspec_item* items; } ;
struct ref {int dummy; } ;

/* Variables and functions */
 int match_explicit_lhs (struct ref*,struct refspec_item*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int check_push_refs(struct ref *src, struct refspec *rs)
{
	int ret = 0;
	int i;

	for (i = 0; i < rs->nr; i++) {
		struct refspec_item *item = &rs->items[i];

		if (item->pattern || item->matching)
			continue;

		ret |= match_explicit_lhs(src, item, NULL, NULL);
	}

	return ret;
}