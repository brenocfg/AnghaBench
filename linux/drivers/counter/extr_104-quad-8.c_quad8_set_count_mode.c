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
struct quad8_iio {int base; unsigned int* count_mode; int* quadrature_scale; scalar_t__* quadrature_mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;

/* Variables and functions */
 unsigned int QUAD8_CTR_CMR ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  outb (unsigned int,int const) ; 

__attribute__((used)) static int quad8_set_count_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, unsigned int cnt_mode)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	unsigned int mode_cfg = cnt_mode << 1;
	const int base_offset = priv->base + 2 * chan->channel + 1;

	priv->count_mode[chan->channel] = cnt_mode;

	/* Add quadrature mode configuration */
	if (priv->quadrature_mode[chan->channel])
		mode_cfg |= (priv->quadrature_scale[chan->channel] + 1) << 3;

	/* Load mode configuration to Counter Mode Register */
	outb(QUAD8_CTR_CMR | mode_cfg, base_offset);

	return 0;
}