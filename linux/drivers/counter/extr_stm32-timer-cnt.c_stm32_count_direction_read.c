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
struct stm32_timer_cnt {int /*<<< orphan*/  regmap; } ;
struct counter_device {struct stm32_timer_cnt* priv; } ;
struct counter_count {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_DIR ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static ssize_t stm32_count_direction_read(struct counter_device *counter,
				      struct counter_count *count,
				      void *private, char *buf)
{
	struct stm32_timer_cnt *const priv = counter->priv;
	const char *direction;
	u32 cr1;

	regmap_read(priv->regmap, TIM_CR1, &cr1);
	direction = (cr1 & TIM_CR1_DIR) ? "backward" : "forward";

	return scnprintf(buf, PAGE_SIZE, "%s\n", direction);
}