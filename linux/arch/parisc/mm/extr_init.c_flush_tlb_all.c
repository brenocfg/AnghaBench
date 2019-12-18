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
 int /*<<< orphan*/  __inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_all_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_tlb_count ; 
 int /*<<< orphan*/  recycle_sids () ; 
 int /*<<< orphan*/  sid_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void flush_tlb_all(void)
{
	__inc_irq_stat(irq_tlb_count);
	spin_lock(&sid_lock);
	flush_tlb_all_local(NULL);
	recycle_sids();
	spin_unlock(&sid_lock);
}