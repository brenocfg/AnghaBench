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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_get_irq_info (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xive_native_alloc_irq () ; 
 int /*<<< orphan*/  xive_native_free_irq (scalar_t__) ; 

int pnv_ocxl_alloc_xive_irq(u32 *irq, u64 *trigger_addr)
{
	__be64 flags, trigger_page;
	s64 rc;
	u32 hwirq;

	hwirq = xive_native_alloc_irq();
	if (!hwirq)
		return -ENOENT;

	rc = opal_xive_get_irq_info(hwirq, &flags, NULL, &trigger_page, NULL,
				NULL);
	if (rc || !trigger_page) {
		xive_native_free_irq(hwirq);
		return -ENOENT;
	}
	*irq = hwirq;
	*trigger_addr = be64_to_cpu(trigger_page);
	return 0;

}