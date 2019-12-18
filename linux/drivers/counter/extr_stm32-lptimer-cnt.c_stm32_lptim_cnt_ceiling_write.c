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
struct stm32_lptim_cnt {int dummy; } ;
struct counter_device {struct stm32_lptim_cnt* priv; } ;
struct counter_count {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  stm32_lptim_cnt_set_ceiling (struct stm32_lptim_cnt* const,char const*,size_t) ; 

__attribute__((used)) static ssize_t stm32_lptim_cnt_ceiling_write(struct counter_device *counter,
					     struct counter_count *count,
					     void *private,
					     const char *buf, size_t len)
{
	struct stm32_lptim_cnt *const priv = counter->priv;

	return stm32_lptim_cnt_set_ceiling(priv, buf, len);
}