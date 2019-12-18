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
struct counter_device_enum_ext {int (* set ) (struct counter_device*,scalar_t__) ;int /*<<< orphan*/  num_items; int /*<<< orphan*/  items; } ;
struct counter_device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ __sysfs_match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int stub1 (struct counter_device*,scalar_t__) ; 

ssize_t counter_device_enum_write(struct counter_device *counter, void *priv,
				  const char *buf, size_t len)
{
	const struct counter_device_enum_ext *const e = priv;
	ssize_t index;
	int err;

	if (!e->set)
		return -EINVAL;

	index = __sysfs_match_string(e->items, e->num_items, buf);
	if (index < 0)
		return index;

	err = e->set(counter, index);
	if (err)
		return err;

	return len;
}