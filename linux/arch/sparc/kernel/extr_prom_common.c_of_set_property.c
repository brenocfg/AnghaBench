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
struct property {int length; struct property* next; void* value; int /*<<< orphan*/  name; } ;
struct device_node {int /*<<< orphan*/  phandle; struct property* properties; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OF_IS_DYNAMIC (struct property*) ; 
 int /*<<< orphan*/  OF_MARK_DYNAMIC (struct property*) ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_set_property_mutex ; 
 int prom_setprop (int /*<<< orphan*/ ,char const*,void*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

int of_set_property(struct device_node *dp, const char *name, void *val, int len)
{
	struct property **prevp;
	unsigned long flags;
	void *new_val;
	int err;

	new_val = kmemdup(val, len, GFP_KERNEL);
	if (!new_val)
		return -ENOMEM;

	err = -ENODEV;

	mutex_lock(&of_set_property_mutex);
	raw_spin_lock_irqsave(&devtree_lock, flags);
	prevp = &dp->properties;
	while (*prevp) {
		struct property *prop = *prevp;

		if (!strcasecmp(prop->name, name)) {
			void *old_val = prop->value;
			int ret;

			ret = prom_setprop(dp->phandle, name, val, len);

			err = -EINVAL;
			if (ret >= 0) {
				prop->value = new_val;
				prop->length = len;

				if (OF_IS_DYNAMIC(prop))
					kfree(old_val);

				OF_MARK_DYNAMIC(prop);

				err = 0;
			}
			break;
		}
		prevp = &(*prevp)->next;
	}
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	mutex_unlock(&of_set_property_mutex);

	/* XXX Upate procfs if necessary... */

	return err;
}