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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int /*<<< orphan*/  tpc; } ;
struct perf_callchain_entry_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  fault_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_32BIT ; 
 TYPE_2__* current ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  flushw_user () ; 
 int /*<<< orphan*/  get_thread_fault_code () ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_callchain_user_32 (struct perf_callchain_entry_ctx*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_callchain_user_64 (struct perf_callchain_entry_ctx*,struct pt_regs*) ; 
 int /*<<< orphan*/  set_thread_fault_code (int /*<<< orphan*/ ) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

void
perf_callchain_user(struct perf_callchain_entry_ctx *entry, struct pt_regs *regs)
{
	u64 saved_fault_address = current_thread_info()->fault_address;
	u8 saved_fault_code = get_thread_fault_code();

	perf_callchain_store(entry, regs->tpc);

	if (!current->mm)
		return;

	flushw_user();

	pagefault_disable();

	if (test_thread_flag(TIF_32BIT))
		perf_callchain_user_32(entry, regs);
	else
		perf_callchain_user_64(entry, regs);

	pagefault_enable();

	set_thread_fault_code(saved_fault_code);
	current_thread_info()->fault_address = saved_fault_address;
}