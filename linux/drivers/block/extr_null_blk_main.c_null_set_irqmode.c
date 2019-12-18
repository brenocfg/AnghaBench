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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_IRQ_NONE ; 
 int /*<<< orphan*/  NULL_IRQ_TIMER ; 
 int /*<<< orphan*/  g_irqmode ; 
 int null_param_store_val (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int null_set_irqmode(const char *str, const struct kernel_param *kp)
{
	return null_param_store_val(str, &g_irqmode, NULL_IRQ_NONE,
					NULL_IRQ_TIMER);
}