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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stm32_lptim_is_enabled (struct stm32_lptim_cnt* const) ; 

__attribute__((used)) static ssize_t stm32_lptim_cnt_enable_read(struct counter_device *counter,
					   struct counter_count *count,
					   void *private, char *buf)
{
	struct stm32_lptim_cnt *const priv = counter->priv;
	int ret;

	ret = stm32_lptim_is_enabled(priv);
	if (ret < 0)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "%u\n", ret);
}