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
typedef  int uint32_t ;
struct t4_range {int size; int start; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  mem_ranges ;

/* Variables and functions */
 int /*<<< orphan*/  A_MA_EDRAM0_BAR ; 
 int /*<<< orphan*/  A_MA_EDRAM1_BAR ; 
 int /*<<< orphan*/  A_MA_EXT_MEMORY1_BAR ; 
 int /*<<< orphan*/  A_MA_EXT_MEMORY_BAR ; 
 int /*<<< orphan*/  A_MA_TARGET_MEM_ENABLE ; 
 int EFAULT ; 
 int EINVAL ; 
 int F_EDRAM0_ENABLE ; 
 int F_EDRAM1_ENABLE ; 
 int F_EXT_MEM1_ENABLE ; 
 int F_EXT_MEM_ENABLE ; 
 int G_EDRAM0_BASE (int) ; 
 int G_EDRAM0_SIZE (int) ; 
 int G_EDRAM1_BASE (int) ; 
 int G_EDRAM1_SIZE (int) ; 
 int G_EXT_MEM1_BASE (int) ; 
 int G_EXT_MEM1_SIZE (int) ; 
 int G_EXT_MEM_BASE (int) ; 
 int G_EXT_MEM_SIZE (int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  bzero (struct t4_range*,int) ; 
 scalar_t__ is_t5 (struct adapter*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct t4_range*,struct t4_range*,int) ; 
 int nitems (struct t4_range*) ; 
 int /*<<< orphan*/  qsort (struct t4_range*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_range_cmp ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
validate_mem_range(struct adapter *sc, uint32_t addr, uint32_t len)
{
	struct t4_range mem_ranges[4], *r, *next;
	uint32_t em, addr_len;
	int i, n, remaining;

	/* Memory can only be accessed in naturally aligned 4 byte units */
	if (addr & 3 || len & 3 || len == 0)
		return (EINVAL);

	/* Enabled memories */
	em = t4_read_reg(sc, A_MA_TARGET_MEM_ENABLE);

	r = &mem_ranges[0];
	n = 0;
	bzero(r, sizeof(mem_ranges));
	if (em & F_EDRAM0_ENABLE) {
		addr_len = t4_read_reg(sc, A_MA_EDRAM0_BAR);
		r->size = G_EDRAM0_SIZE(addr_len) << 20;
		if (r->size > 0) {
			r->start = G_EDRAM0_BASE(addr_len) << 20;
			if (addr >= r->start &&
			    addr + len <= r->start + r->size)
				return (0);
			r++;
			n++;
		}
	}
	if (em & F_EDRAM1_ENABLE) {
		addr_len = t4_read_reg(sc, A_MA_EDRAM1_BAR);
		r->size = G_EDRAM1_SIZE(addr_len) << 20;
		if (r->size > 0) {
			r->start = G_EDRAM1_BASE(addr_len) << 20;
			if (addr >= r->start &&
			    addr + len <= r->start + r->size)
				return (0);
			r++;
			n++;
		}
	}
	if (em & F_EXT_MEM_ENABLE) {
		addr_len = t4_read_reg(sc, A_MA_EXT_MEMORY_BAR);
		r->size = G_EXT_MEM_SIZE(addr_len) << 20;
		if (r->size > 0) {
			r->start = G_EXT_MEM_BASE(addr_len) << 20;
			if (addr >= r->start &&
			    addr + len <= r->start + r->size)
				return (0);
			r++;
			n++;
		}
	}
	if (is_t5(sc) && em & F_EXT_MEM1_ENABLE) {
		addr_len = t4_read_reg(sc, A_MA_EXT_MEMORY1_BAR);
		r->size = G_EXT_MEM1_SIZE(addr_len) << 20;
		if (r->size > 0) {
			r->start = G_EXT_MEM1_BASE(addr_len) << 20;
			if (addr >= r->start &&
			    addr + len <= r->start + r->size)
				return (0);
			r++;
			n++;
		}
	}
	MPASS(n <= nitems(mem_ranges));

	if (n > 1) {
		/* Sort and merge the ranges. */
		qsort(mem_ranges, n, sizeof(struct t4_range), t4_range_cmp);

		/* Start from index 0 and examine the next n - 1 entries. */
		r = &mem_ranges[0];
		for (remaining = n - 1; remaining > 0; remaining--, r++) {

			MPASS(r->size > 0);	/* r is a valid entry. */
			next = r + 1;
			MPASS(next->size > 0);	/* and so is the next one. */

			while (r->start + r->size >= next->start) {
				/* Merge the next one into the current entry. */
				r->size = max(r->start + r->size,
				    next->start + next->size) - r->start;
				n--;	/* One fewer entry in total. */
				if (--remaining == 0)
					goto done;	/* short circuit */
				next++;
			}
			if (next != r + 1) {
				/*
				 * Some entries were merged into r and next
				 * points to the first valid entry that couldn't
				 * be merged.
				 */
				MPASS(next->size > 0);	/* must be valid */
				memcpy(r + 1, next, remaining * sizeof(*r));
#ifdef INVARIANTS
				/*
				 * This so that the foo->size assertion in the
				 * next iteration of the loop do the right
				 * thing for entries that were pulled up and are
				 * no longer valid.
				 */
				MPASS(n < nitems(mem_ranges));
				bzero(&mem_ranges[n], (nitems(mem_ranges) - n) *
				    sizeof(struct t4_range));
#endif
			}
		}
done:
		/* Done merging the ranges. */
		MPASS(n > 0);
		r = &mem_ranges[0];
		for (i = 0; i < n; i++, r++) {
			if (addr >= r->start &&
			    addr + len <= r->start + r->size)
				return (0);
		}
	}

	return (EFAULT);
}