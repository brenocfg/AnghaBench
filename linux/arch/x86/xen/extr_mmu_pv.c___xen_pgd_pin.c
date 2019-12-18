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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMUEXT_PIN_L3_TABLE ; 
 int /*<<< orphan*/  MMUEXT_PIN_L4_TABLE ; 
 int /*<<< orphan*/  PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_PGD ; 
 int /*<<< orphan*/  PT_PMD ; 
 int /*<<< orphan*/  TASK_SIZE ; 
 int /*<<< orphan*/  USER_LIMIT ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 scalar_t__ __xen_pgd_walk (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap_flush_unused () ; 
 size_t pgd_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xen_mmu_pgd_pin (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_do_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xen_get_user_pgd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_pin_page (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __xen_pgd_pin(struct mm_struct *mm, pgd_t *pgd)
{
	trace_xen_mmu_pgd_pin(mm, pgd);

	xen_mc_batch();

	if (__xen_pgd_walk(mm, pgd, xen_pin_page, USER_LIMIT)) {
		/* re-enable interrupts for flushing */
		xen_mc_issue(0);

		kmap_flush_unused();

		xen_mc_batch();
	}

#ifdef CONFIG_X86_64
	{
		pgd_t *user_pgd = xen_get_user_pgd(pgd);

		xen_do_pin(MMUEXT_PIN_L4_TABLE, PFN_DOWN(__pa(pgd)));

		if (user_pgd) {
			xen_pin_page(mm, virt_to_page(user_pgd), PT_PGD);
			xen_do_pin(MMUEXT_PIN_L4_TABLE,
				   PFN_DOWN(__pa(user_pgd)));
		}
	}
#else /* CONFIG_X86_32 */
#ifdef CONFIG_X86_PAE
	/* Need to make sure unshared kernel PMD is pinnable */
	xen_pin_page(mm, pgd_page(pgd[pgd_index(TASK_SIZE)]),
		     PT_PMD);
#endif
	xen_do_pin(MMUEXT_PIN_L3_TABLE, PFN_DOWN(__pa(pgd)));
#endif /* CONFIG_X86_64 */
	xen_mc_issue(0);
}