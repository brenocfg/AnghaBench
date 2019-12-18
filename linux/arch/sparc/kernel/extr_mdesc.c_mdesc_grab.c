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
struct mdesc_handle {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 struct mdesc_handle* cur_mdesc ; 
 int /*<<< orphan*/  mdesc_lock ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct mdesc_handle *mdesc_grab(void)
{
	struct mdesc_handle *hp;
	unsigned long flags;

	spin_lock_irqsave(&mdesc_lock, flags);
	hp = cur_mdesc;
	if (hp)
		refcount_inc(&hp->refcnt);
	spin_unlock_irqrestore(&mdesc_lock, flags);

	return hp;
}