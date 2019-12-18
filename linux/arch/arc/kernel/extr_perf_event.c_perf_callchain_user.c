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
struct pt_regs {int dummy; } ;
struct perf_callchain_entry_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry_ctx*,int /*<<< orphan*/ ) ; 

void perf_callchain_user(struct perf_callchain_entry_ctx *entry,
			 struct pt_regs *regs)
{
	/*
	 * User stack can't be unwound trivially with kernel dwarf unwinder
	 * So for now just record the user PC
	 */
	perf_callchain_store(entry, instruction_pointer(regs));
}