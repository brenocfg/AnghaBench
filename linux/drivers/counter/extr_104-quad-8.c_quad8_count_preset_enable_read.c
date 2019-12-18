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
struct quad8_iio {int /*<<< orphan*/ * preset_enable; } ;
struct counter_device {struct quad8_iio* priv; } ;
struct counter_count {size_t id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t quad8_count_preset_enable_read(struct counter_device *counter,
	struct counter_count *count, void *private, char *buf)
{
	const struct quad8_iio *const priv = counter->priv;

	return sprintf(buf, "%u\n", !priv->preset_enable[count->id]);
}