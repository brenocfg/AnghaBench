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
typedef  scalar_t__ u32 ;
struct stm32_timer_cnt {scalar_t__ ceiling; int /*<<< orphan*/  regmap; } ;
struct counter_device {struct stm32_timer_cnt* priv; } ;
struct counter_count_write_value {int dummy; } ;
struct counter_count {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_COUNT_POSITION ; 
 int EINVAL ; 
 int /*<<< orphan*/  TIM_CNT ; 
 int counter_count_write_value_get (scalar_t__*,int /*<<< orphan*/ ,struct counter_count_write_value*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stm32_count_write(struct counter_device *counter,
			     struct counter_count *count,
			     struct counter_count_write_value *val)
{
	struct stm32_timer_cnt *const priv = counter->priv;
	u32 cnt;
	int err;

	err = counter_count_write_value_get(&cnt, COUNTER_COUNT_POSITION, val);
	if (err)
		return err;

	if (cnt > priv->ceiling)
		return -EINVAL;

	return regmap_write(priv->regmap, TIM_CNT, cnt);
}