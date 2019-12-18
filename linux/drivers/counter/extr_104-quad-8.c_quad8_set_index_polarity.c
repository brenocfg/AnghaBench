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
struct quad8_iio {unsigned int* synchronous_mode; int base; unsigned int* index_polarity; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 unsigned int const QUAD8_CTR_IDR ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  outb (unsigned int const,int const) ; 

__attribute__((used)) static int quad8_set_index_polarity(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, unsigned int index_polarity)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	const unsigned int idr_cfg = priv->synchronous_mode[chan->channel] |
		index_polarity << 1;
	const int base_offset = priv->base + 2 * chan->channel + 1;

	priv->index_polarity[chan->channel] = index_polarity;

	/* Load Index Control configuration to Index Control Register */
	outb(QUAD8_CTR_IDR | idr_cfg, base_offset);

	return 0;
}