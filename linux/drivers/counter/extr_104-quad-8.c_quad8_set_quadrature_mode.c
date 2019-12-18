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
struct quad8_iio {int* count_mode; int base; int* quadrature_scale; unsigned int* quadrature_mode; scalar_t__* synchronous_mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 unsigned int QUAD8_CTR_CMR ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  outb (unsigned int,int const) ; 
 int /*<<< orphan*/  quad8_set_synchronous_mode (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int quad8_set_quadrature_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, unsigned int quadrature_mode)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	unsigned int mode_cfg = priv->count_mode[chan->channel] << 1;
	const int base_offset = priv->base + 2 * chan->channel + 1;

	if (quadrature_mode)
		mode_cfg |= (priv->quadrature_scale[chan->channel] + 1) << 3;
	else {
		/* Quadrature scaling only available in quadrature mode */
		priv->quadrature_scale[chan->channel] = 0;

		/* Synchronous function not supported in non-quadrature mode */
		if (priv->synchronous_mode[chan->channel])
			quad8_set_synchronous_mode(indio_dev, chan, 0);
	}

	priv->quadrature_mode[chan->channel] = quadrature_mode;

	/* Load mode configuration to Counter Mode Register */
	outb(QUAD8_CTR_CMR | mode_cfg, base_offset);

	return 0;
}