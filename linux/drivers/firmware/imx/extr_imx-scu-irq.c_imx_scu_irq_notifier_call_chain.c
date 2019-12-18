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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*) ; 
 int /*<<< orphan*/  imx_scu_irq_notifier_chain ; 

__attribute__((used)) static int imx_scu_irq_notifier_call_chain(unsigned long status, u8 *group)
{
	return atomic_notifier_call_chain(&imx_scu_irq_notifier_chain,
		status, (void *)group);
}