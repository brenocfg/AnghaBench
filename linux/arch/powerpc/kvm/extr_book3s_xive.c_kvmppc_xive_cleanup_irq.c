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
struct xive_irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKED ; 
 int /*<<< orphan*/  XIVE_ESB_SET_PQ_01 ; 
 int /*<<< orphan*/  xive_native_configure_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vm_esb_load (struct xive_irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_xive_cleanup_irq(u32 hw_num, struct xive_irq_data *xd)
{
	xive_vm_esb_load(xd, XIVE_ESB_SET_PQ_01);
	xive_native_configure_irq(hw_num, 0, MASKED, 0);
}