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
struct flush_tlb_info {scalar_t__ mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  loaded_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_TLB_REMOTE_FLUSH_RECEIVED ; 
 int /*<<< orphan*/  TLB_REMOTE_SHOOTDOWN ; 
 int /*<<< orphan*/  count_vm_tlb_event (int /*<<< orphan*/ ) ; 
 TYPE_1__ cpu_tlbstate ; 
 int /*<<< orphan*/  flush_tlb_func_common (struct flush_tlb_info const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_tlb_count ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_tlb_func_remote(void *info)
{
	const struct flush_tlb_info *f = info;

	inc_irq_stat(irq_tlb_count);

	if (f->mm && f->mm != this_cpu_read(cpu_tlbstate.loaded_mm))
		return;

	count_vm_tlb_event(NR_TLB_REMOTE_FLUSH_RECEIVED);
	flush_tlb_func_common(f, false, TLB_REMOTE_SHOOTDOWN);
}