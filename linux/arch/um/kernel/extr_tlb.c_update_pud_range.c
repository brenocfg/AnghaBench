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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int add_munmap (unsigned long,unsigned long,struct host_vm_change*) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pud_mkuptodate (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_newpage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int update_pmd_range (int /*<<< orphan*/ *,unsigned long,unsigned long,struct host_vm_change*) ; 

__attribute__((used)) static inline int update_pud_range(pgd_t *pgd, unsigned long addr,
				   unsigned long end,
				   struct host_vm_change *hvc)
{
	pud_t *pud;
	unsigned long next;
	int ret = 0;

	pud = pud_offset(pgd, addr);
	do {
		next = pud_addr_end(addr, end);
		if (!pud_present(*pud)) {
			if (hvc->force || pud_newpage(*pud)) {
				ret = add_munmap(addr, next - addr, hvc);
				pud_mkuptodate(*pud);
			}
		}
		else ret = update_pmd_range(pud, addr, next, hvc);
	} while (pud++, addr = next, ((addr < end) && !ret));
	return ret;
}