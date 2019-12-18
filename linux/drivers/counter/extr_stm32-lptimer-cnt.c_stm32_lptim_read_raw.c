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
typedef  int u32 ;
struct stm32_lptim_cnt {int polarity; int /*<<< orphan*/  quadrature_mode; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_ENABLE 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  STM32_LPTIM_CNT ; 
 struct stm32_lptim_cnt* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stm32_lptim_is_enabled (struct stm32_lptim_cnt*) ; 

__attribute__((used)) static int stm32_lptim_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct stm32_lptim_cnt *priv = iio_priv(indio_dev);
	u32 dat;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = regmap_read(priv->regmap, STM32_LPTIM_CNT, &dat);
		if (ret)
			return ret;
		*val = dat;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_ENABLE:
		ret = stm32_lptim_is_enabled(priv);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		/* Non-quadrature mode: scale = 1 */
		*val = 1;
		*val2 = 0;
		if (priv->quadrature_mode) {
			/*
			 * Quadrature encoder mode:
			 * - both edges, quarter cycle, scale is 0.25
			 * - either rising/falling edge scale is 0.5
			 */
			if (priv->polarity > 1)
				*val2 = 2;
			else
				*val2 = 1;
		}
		return IIO_VAL_FRACTIONAL_LOG2;

	default:
		return -EINVAL;
	}
}