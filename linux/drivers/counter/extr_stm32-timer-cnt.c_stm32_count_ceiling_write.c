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
struct stm32_timer_cnt {unsigned int ceiling; int /*<<< orphan*/  regmap; } ;
struct counter_device {struct stm32_timer_cnt* priv; } ;
struct counter_count {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_ARR ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int /*<<< orphan*/  TIM_CR1_ARPE ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static ssize_t stm32_count_ceiling_write(struct counter_device *counter,
					 struct counter_count *count,
					 void *private,
					 const char *buf, size_t len)
{
	struct stm32_timer_cnt *const priv = counter->priv;
	unsigned int ceiling;
	int ret;

	ret = kstrtouint(buf, 0, &ceiling);
	if (ret)
		return ret;

	/* TIMx_ARR register shouldn't be buffered (ARPE=0) */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, 0);
	regmap_write(priv->regmap, TIM_ARR, ceiling);

	priv->ceiling = ceiling;
	return len;
}