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
struct pg_state {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void walk_pte(struct pg_state *st, pmd_t *pmdp, unsigned long start,
		     unsigned long end)
{
	unsigned long addr = start;
	pte_t *ptep = pte_offset_kernel(pmdp, start);

	do {
		note_page(st, addr, 4, READ_ONCE(pte_val(*ptep)));
	} while (ptep++, addr += PAGE_SIZE, addr != end);
}