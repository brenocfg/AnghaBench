#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_desc {int /*<<< orphan*/  kstat_irqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  irqs_sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 TYPE_1__ kstat ; 
 int /*<<< orphan*/  this_cpu_inc_rm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_rm_handle_irq_desc(struct irq_desc *desc)
{
	this_cpu_inc_rm(desc->kstat_irqs);
	__this_cpu_inc(kstat.irqs_sum);
}