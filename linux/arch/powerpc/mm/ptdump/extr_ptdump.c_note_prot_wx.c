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
struct pg_state {int current_flags; unsigned long start_address; unsigned long wx_pages; int /*<<< orphan*/  check_wx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_DEBUG_WX ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_KERNEL_X ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,void*,void*) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void note_prot_wx(struct pg_state *st, unsigned long addr)
{
	if (!IS_ENABLED(CONFIG_PPC_DEBUG_WX) || !st->check_wx)
		return;

	if (!((st->current_flags & pgprot_val(PAGE_KERNEL_X)) == pgprot_val(PAGE_KERNEL_X)))
		return;

	WARN_ONCE(1, "powerpc/mm: Found insecure W+X mapping at address %p/%pS\n",
		  (void *)st->start_address, (void *)st->start_address);

	st->wx_pages += (addr - st->start_address) / PAGE_SIZE;
}