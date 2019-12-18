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
struct pmb_entry {int vpn; int ppn; int flags; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int PMB_V ; 
 int /*<<< orphan*/  __raw_writel (int,unsigned long) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 unsigned long mk_pmb_addr (int /*<<< orphan*/ ) ; 
 unsigned long mk_pmb_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_pmb_entry(struct pmb_entry *pmbe)
{
	unsigned long addr, data;

	addr = mk_pmb_addr(pmbe->entry);
	data = mk_pmb_data(pmbe->entry);

	jump_to_uncached();

	/* Set V-bit */
	__raw_writel(pmbe->vpn | PMB_V, addr);
	__raw_writel(pmbe->ppn | pmbe->flags | PMB_V, data);

	back_to_cached();
}