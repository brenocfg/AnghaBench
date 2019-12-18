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
struct stm32_lptim_cnt {scalar_t__ ceiling; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ STM32_LPTIM_MAX_ARR ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stm32_lptim_is_enabled (struct stm32_lptim_cnt*) ; 

__attribute__((used)) static ssize_t stm32_lptim_cnt_set_ceiling(struct stm32_lptim_cnt *priv,
					   const char *buf, size_t len)
{
	int ret;

	if (stm32_lptim_is_enabled(priv))
		return -EBUSY;

	ret = kstrtouint(buf, 0, &priv->ceiling);
	if (ret)
		return ret;

	if (priv->ceiling > STM32_LPTIM_MAX_ARR)
		return -EINVAL;

	return len;
}