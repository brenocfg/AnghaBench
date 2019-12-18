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
 int /*<<< orphan*/  __flush_tlb_all () ; 
 int /*<<< orphan*/  broadcast_tlb_a15_erratum () ; 
 int /*<<< orphan*/  ipi_flush_tlb_all ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlb_ops_need_broadcast () ; 

void flush_tlb_all(void)
{
	if (tlb_ops_need_broadcast())
		on_each_cpu(ipi_flush_tlb_all, NULL, 1);
	else
		__flush_tlb_all();
	broadcast_tlb_a15_erratum();
}