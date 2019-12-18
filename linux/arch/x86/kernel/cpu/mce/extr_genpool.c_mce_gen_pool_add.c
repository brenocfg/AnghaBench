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
struct mce_evt_llist {int /*<<< orphan*/  llnode; int /*<<< orphan*/  mce; } ;
struct mce {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ filter_mce (struct mce*) ; 
 scalar_t__ gen_pool_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_event_llist ; 
 int /*<<< orphan*/  mce_evt_pool ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mce*,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*) ; 

int mce_gen_pool_add(struct mce *mce)
{
	struct mce_evt_llist *node;

	if (filter_mce(mce))
		return -EINVAL;

	if (!mce_evt_pool)
		return -EINVAL;

	node = (void *)gen_pool_alloc(mce_evt_pool, sizeof(*node));
	if (!node) {
		pr_warn_ratelimited("MCE records pool full!\n");
		return -ENOMEM;
	}

	memcpy(&node->mce, mce, sizeof(*mce));
	llist_add(&node->llnode, &mce_event_llist);

	return 0;
}