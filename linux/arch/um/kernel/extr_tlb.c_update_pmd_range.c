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
struct host_vm_change {scalar_t__ force; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int add_munmap (unsigned long,unsigned long,struct host_vm_change*) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pmd_mkuptodate (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_newpage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int update_pte_range (int /*<<< orphan*/ *,unsigned long,unsigned long,struct host_vm_change*) ; 

__attribute__((used)) static inline int update_pmd_range(pud_t *pud, unsigned long addr,
				   unsigned long end,
				   struct host_vm_change *hvc)
{
	pmd_t *pmd;
	unsigned long next;
	int ret = 0;

	pmd = pmd_offset(pud, addr);
	do {
		next = pmd_addr_end(addr, end);
		if (!pmd_present(*pmd)) {
			if (hvc->force || pmd_newpage(*pmd)) {
				ret = add_munmap(addr, next - addr, hvc);
				pmd_mkuptodate(*pmd);
			}
		}
		else ret = update_pte_range(pmd, addr, next, hvc);
	} while (pmd++, addr = next, ((addr < end) && !ret));
	return ret;
}