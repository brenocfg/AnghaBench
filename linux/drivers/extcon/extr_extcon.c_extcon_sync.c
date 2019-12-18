#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct extcon_dev {int state; TYPE_1__ dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  nh_all; int /*<<< orphan*/ * nh; } ;
typedef  int /*<<< orphan*/  state_buf ;
typedef  int /*<<< orphan*/  name_buf ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int find_cable_index_by_id (struct extcon_dev*,unsigned int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int name_show (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  raw_notifier_call_chain (int /*<<< orphan*/ *,int,struct extcon_dev*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int state_show (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

int extcon_sync(struct extcon_dev *edev, unsigned int id)
{
	char name_buf[120];
	char state_buf[120];
	char *prop_buf;
	char *envp[3];
	int env_offset = 0;
	int length;
	int index;
	int state;
	unsigned long flags;

	if (!edev)
		return -EINVAL;

	index = find_cable_index_by_id(edev, id);
	if (index < 0)
		return index;

	spin_lock_irqsave(&edev->lock, flags);
	state = !!(edev->state & BIT(index));
	spin_unlock_irqrestore(&edev->lock, flags);

	/*
	 * Call functions in a raw notifier chain for the specific one
	 * external connector.
	 */
	raw_notifier_call_chain(&edev->nh[index], state, edev);

	/*
	 * Call functions in a raw notifier chain for the all supported
	 * external connectors.
	 */
	raw_notifier_call_chain(&edev->nh_all, state, edev);

	spin_lock_irqsave(&edev->lock, flags);
	/* This could be in interrupt handler */
	prop_buf = (char *)get_zeroed_page(GFP_ATOMIC);
	if (!prop_buf) {
		/* Unlock early before uevent */
		spin_unlock_irqrestore(&edev->lock, flags);

		dev_err(&edev->dev, "out of memory in extcon_set_state\n");
		kobject_uevent(&edev->dev.kobj, KOBJ_CHANGE);

		return -ENOMEM;
	}

	length = name_show(&edev->dev, NULL, prop_buf);
	if (length > 0) {
		if (prop_buf[length - 1] == '\n')
			prop_buf[length - 1] = 0;
		snprintf(name_buf, sizeof(name_buf), "NAME=%s", prop_buf);
		envp[env_offset++] = name_buf;
	}

	length = state_show(&edev->dev, NULL, prop_buf);
	if (length > 0) {
		if (prop_buf[length - 1] == '\n')
			prop_buf[length - 1] = 0;
		snprintf(state_buf, sizeof(state_buf), "STATE=%s", prop_buf);
		envp[env_offset++] = state_buf;
	}
	envp[env_offset] = NULL;

	/* Unlock early before uevent */
	spin_unlock_irqrestore(&edev->lock, flags);
	kobject_uevent_env(&edev->dev.kobj, KOBJ_CHANGE, envp);
	free_page((unsigned long)prop_buf);

	return 0;
}