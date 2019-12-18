#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ irq_bypass_add_producer; } ;
struct TYPE_3__ {scalar_t__ irq_bypass_add_producer; } ;

/* Variables and functions */
 TYPE_2__* kvmppc_hv_ops ; 
 TYPE_1__* kvmppc_pr_ops ; 

bool kvm_arch_has_irq_bypass(void)
{
	return ((kvmppc_hv_ops && kvmppc_hv_ops->irq_bypass_add_producer) ||
		(kvmppc_pr_ops && kvmppc_pr_ops->irq_bypass_add_producer));
}