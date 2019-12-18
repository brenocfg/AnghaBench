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
struct quad8_iio {int base; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;

/* Variables and functions */
 int QUAD8_FLAG_UD ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int inb (int const) ; 

__attribute__((used)) static int quad8_get_count_direction(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	const int base_offset = priv->base + 2 * chan->channel + 1;

	return !!(inb(base_offset) & QUAD8_FLAG_UD);
}