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
struct quad8_iio {int base; int* ab_enable; int* quadrature_scale; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_ENABLE 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_INDEX ; 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int QUAD8_CTR_RLD ; 
 unsigned int QUAD8_FLAG_BT ; 
 unsigned int QUAD8_FLAG_CT ; 
 int /*<<< orphan*/  QUAD8_REG_INDEX_INPUT_LEVELS ; 
 int QUAD8_RLD_CNTR_OUT ; 
 int QUAD8_RLD_RESET_BP ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 unsigned int inb (int const) ; 
 int /*<<< orphan*/  outb (int,int const) ; 

__attribute__((used)) static int quad8_read_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int *val, int *val2, long mask)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	const int base_offset = priv->base + 2 * chan->channel;
	unsigned int flags;
	unsigned int borrow;
	unsigned int carry;
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type == IIO_INDEX) {
			*val = !!(inb(priv->base + QUAD8_REG_INDEX_INPUT_LEVELS)
				& BIT(chan->channel));
			return IIO_VAL_INT;
		}

		flags = inb(base_offset + 1);
		borrow = flags & QUAD8_FLAG_BT;
		carry = !!(flags & QUAD8_FLAG_CT);

		/* Borrow XOR Carry effectively doubles count range */
		*val = (borrow ^ carry) << 24;

		/* Reset Byte Pointer; transfer Counter to Output Latch */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP | QUAD8_RLD_CNTR_OUT,
		     base_offset + 1);

		for (i = 0; i < 3; i++)
			*val |= (unsigned int)inb(base_offset) << (8 * i);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_ENABLE:
		*val = priv->ab_enable[chan->channel];
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 1;
		*val2 = priv->quadrature_scale[chan->channel];
		return IIO_VAL_FRACTIONAL_LOG2;
	}

	return -EINVAL;
}