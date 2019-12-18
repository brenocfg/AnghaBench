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
 int /*<<< orphan*/  call_do_softirq (int /*<<< orphan*/ ) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/ * softirq_ctx ; 

void do_softirq_own_stack(void)
{
	call_do_softirq(softirq_ctx[smp_processor_id()]);
}