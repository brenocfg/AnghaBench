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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_get_irq_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xive_native_get_irq_config(u32 hw_irq, u32 *target, u8 *prio,
				      u32 *sw_irq)
{
	s64 rc;
	__be64 vp;
	__be32 lirq;

	rc = opal_xive_get_irq_config(hw_irq, &vp, prio, &lirq);

	*target = be64_to_cpu(vp);
	*sw_irq = be32_to_cpu(lirq);

	return rc == 0 ? 0 : -ENXIO;
}