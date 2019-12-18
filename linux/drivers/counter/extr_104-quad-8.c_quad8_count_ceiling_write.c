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
struct quad8_iio {int* count_mode; } ;
struct counter_device {struct quad8_iio* priv; } ;
struct counter_count {size_t id; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t quad8_count_preset_write (struct counter_device*,struct counter_count*,void*,char const*,size_t) ; 

__attribute__((used)) static ssize_t quad8_count_ceiling_write(struct counter_device *counter,
	struct counter_count *count, void *private, const char *buf, size_t len)
{
	struct quad8_iio *const priv = counter->priv;

	/* Range Limit and Modulo-N count modes use preset value as ceiling */
	switch (priv->count_mode[count->id]) {
	case 1:
	case 3:
		return quad8_count_preset_write(counter, count, private, buf,
						len);
	}

	return len;
}