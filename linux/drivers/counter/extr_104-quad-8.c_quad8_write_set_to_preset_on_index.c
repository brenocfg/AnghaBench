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
struct quad8_iio {int base; int* preset_enable; unsigned int* ab_enable; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int QUAD8_CTR_IOR ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  outb (unsigned int,int const) ; 

__attribute__((used)) static ssize_t quad8_write_set_to_preset_on_index(struct iio_dev *indio_dev,
	uintptr_t private, const struct iio_chan_spec *chan, const char *buf,
	size_t len)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	const int base_offset = priv->base + 2 * chan->channel + 1;
	bool preset_enable;
	int ret;
	unsigned int ior_cfg;

	ret = kstrtobool(buf, &preset_enable);
	if (ret)
		return ret;

	/* Preset enable is active low in Input/Output Control register */
	preset_enable = !preset_enable;

	priv->preset_enable[chan->channel] = preset_enable;

	ior_cfg = priv->ab_enable[chan->channel] |
		(unsigned int)preset_enable << 1;

	/* Load I/O control configuration to Input / Output Control Register */
	outb(QUAD8_CTR_IOR | ior_cfg, base_offset);

	return len;
}