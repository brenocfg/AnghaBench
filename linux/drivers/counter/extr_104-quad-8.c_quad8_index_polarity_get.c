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
struct quad8_iio {size_t* index_polarity; } ;
struct counter_signal {int id; } ;
struct counter_device {struct quad8_iio* priv; } ;

/* Variables and functions */

__attribute__((used)) static int quad8_index_polarity_get(struct counter_device *counter,
	struct counter_signal *signal, size_t *index_polarity)
{
	const struct quad8_iio *const priv = counter->priv;
	const size_t channel_id = signal->id - 16;

	*index_polarity = priv->index_polarity[channel_id];

	return 0;
}