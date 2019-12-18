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
struct extcon_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int extcon_set_state (struct extcon_dev*,unsigned int,int) ; 
 int extcon_sync (struct extcon_dev*,unsigned int) ; 
 int find_cable_index_by_id (struct extcon_dev*,unsigned int) ; 
 int is_extcon_changed (struct extcon_dev*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int extcon_set_state_sync(struct extcon_dev *edev, unsigned int id, bool state)
{
	int ret, index;
	unsigned long flags;

	index = find_cable_index_by_id(edev, id);
	if (index < 0)
		return index;

	/* Check whether the external connector's state is changed. */
	spin_lock_irqsave(&edev->lock, flags);
	ret = is_extcon_changed(edev, index, state);
	spin_unlock_irqrestore(&edev->lock, flags);
	if (!ret)
		return 0;

	ret = extcon_set_state(edev, id, state);
	if (ret < 0)
		return ret;

	return extcon_sync(edev, id);
}