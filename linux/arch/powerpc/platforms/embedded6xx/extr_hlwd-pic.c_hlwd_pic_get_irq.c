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

/* Variables and functions */
 unsigned int __hlwd_pic_get_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlwd_irq_host ; 

unsigned int hlwd_pic_get_irq(void)
{
	return __hlwd_pic_get_irq(hlwd_irq_host);
}