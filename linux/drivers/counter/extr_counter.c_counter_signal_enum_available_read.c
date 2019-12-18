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
struct counter_signal_enum_ext {size_t num_items; char** items; } ;
struct counter_signal {int dummy; } ;
struct counter_device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ sprintf (char*,char*,char*) ; 

ssize_t counter_signal_enum_available_read(struct counter_device *counter,
					   struct counter_signal *signal,
					   void *priv, char *buf)
{
	const struct counter_signal_enum_ext *const e = priv;
	size_t i;
	size_t len = 0;

	if (!e->num_items)
		return 0;

	for (i = 0; i < e->num_items; i++)
		len += sprintf(buf + len, "%s\n", e->items[i]);

	return len;
}