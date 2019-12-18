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
struct counter_device {int dummy; } ;
struct counter_count_enum_ext {int (* get ) (struct counter_device*,struct counter_count*,size_t*) ;size_t num_items; char** items; } ;
struct counter_count {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int sprintf (char*,char*,char*) ; 
 int stub1 (struct counter_device*,struct counter_count*,size_t*) ; 

ssize_t counter_count_enum_read(struct counter_device *counter,
				struct counter_count *count, void *priv,
				char *buf)
{
	const struct counter_count_enum_ext *const e = priv;
	int err;
	size_t index;

	if (!e->get)
		return -EINVAL;

	err = e->get(counter, count, &index);
	if (err)
		return err;

	if (index >= e->num_items)
		return -EINVAL;

	return sprintf(buf, "%s\n", e->items[index]);
}