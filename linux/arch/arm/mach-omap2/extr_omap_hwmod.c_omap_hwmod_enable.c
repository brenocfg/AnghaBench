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
struct omap_hwmod {int /*<<< orphan*/  _lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int _enable (struct omap_hwmod*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int omap_hwmod_enable(struct omap_hwmod *oh)
{
	int r;
	unsigned long flags;

	if (!oh)
		return -EINVAL;

	spin_lock_irqsave(&oh->_lock, flags);
	r = _enable(oh);
	spin_unlock_irqrestore(&oh->_lock, flags);

	return r;
}