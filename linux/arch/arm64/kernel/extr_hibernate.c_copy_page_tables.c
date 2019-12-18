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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset_raw (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int copy_page_tables(pgd_t *dst_pgdp, unsigned long start,
			    unsigned long end)
{
	unsigned long next;
	unsigned long addr = start;
	pgd_t *src_pgdp = pgd_offset_k(start);

	dst_pgdp = pgd_offset_raw(dst_pgdp, start);
	do {
		next = pgd_addr_end(addr, end);
		if (pgd_none(READ_ONCE(*src_pgdp)))
			continue;
		if (copy_pud(dst_pgdp, src_pgdp, addr, next))
			return -ENOMEM;
	} while (dst_pgdp++, src_pgdp++, addr = next, addr != end);

	return 0;
}