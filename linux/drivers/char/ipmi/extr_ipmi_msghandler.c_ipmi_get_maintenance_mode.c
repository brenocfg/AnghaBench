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
struct ipmi_user {TYPE_1__* intf; } ;
struct TYPE_2__ {int maintenance_mode; int /*<<< orphan*/  maintenance_mode_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 struct ipmi_user* acquire_ipmi_user (struct ipmi_user*,int*) ; 
 int /*<<< orphan*/  release_ipmi_user (struct ipmi_user*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipmi_get_maintenance_mode(struct ipmi_user *user)
{
	int mode, index;
	unsigned long flags;

	user = acquire_ipmi_user(user, &index);
	if (!user)
		return -ENODEV;

	spin_lock_irqsave(&user->intf->maintenance_mode_lock, flags);
	mode = user->intf->maintenance_mode;
	spin_unlock_irqrestore(&user->intf->maintenance_mode_lock, flags);
	release_ipmi_user(user, index);

	return mode;
}