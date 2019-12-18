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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_timer_cnt {int /*<<< orphan*/  regmap; } ;
struct counter_device {struct stm32_timer_cnt* priv; } ;
struct counter_count_read_value {int dummy; } ;
struct counter_count {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_COUNT_POSITION ; 
 int /*<<< orphan*/  TIM_CNT ; 
 int /*<<< orphan*/  counter_count_read_value_set (struct counter_count_read_value*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_count_read(struct counter_device *counter,
			    struct counter_count *count,
			    struct counter_count_read_value *val)
{
	struct stm32_timer_cnt *const priv = counter->priv;
	u32 cnt;

	regmap_read(priv->regmap, TIM_CNT, &cnt);
	counter_count_read_value_set(val, COUNTER_COUNT_POSITION, &cnt);

	return 0;
}