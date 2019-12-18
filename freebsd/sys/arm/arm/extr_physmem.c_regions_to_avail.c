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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct region {scalar_t__ addr; scalar_t__ size; int flags; } ;

/* Variables and functions */
 size_t excnt ; 
 struct region* exregions ; 
 size_t hwcnt ; 
 struct region* hwregions ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pm_btop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
regions_to_avail(vm_paddr_t *avail, uint32_t exflags, size_t maxavail,
    long *pavail, long *prealmem)
{
	size_t acnt, exi, hwi;
	uint64_t end, start, xend, xstart;
	long availmem, totalmem;
	const struct region *exp, *hwp;

	totalmem = 0;
	availmem = 0;
	acnt = 0;
	for (hwi = 0, hwp = hwregions; hwi < hwcnt; ++hwi, ++hwp) {
		start = hwp->addr;
		end   = hwp->size + start;
		totalmem += pm_btop((vm_offset_t)(end - start));
		for (exi = 0, exp = exregions; exi < excnt; ++exi, ++exp) {
			/*
			 * If the excluded region does not match given flags,
			 * continue checking with the next excluded region.
			 */
			if ((exp->flags & exflags) == 0)
				continue;
			xstart = exp->addr;
			xend   = exp->size + xstart;
			/*
			 * If the excluded region ends before this hw region,
			 * continue checking with the next excluded region.
			 */
			if (xend <= start)
				continue;
			/*
			 * If the excluded region begins after this hw region
			 * we're done because both lists are sorted.
			 */
			if (xstart >= end)
				break;
			/*
			 * If the excluded region completely covers this hw
			 * region, shrink this hw region to zero size.
			 */
			if ((start >= xstart) && (end <= xend)) {
				start = xend;
				end = xend;
				break;
			}
			/*
			 * If the excluded region falls wholly within this hw
			 * region without abutting or overlapping the beginning
			 * or end, create an available entry from the leading
			 * fragment, then adjust the start of this hw region to
			 * the end of the excluded region, and continue checking
			 * the next excluded region because another exclusion
			 * could affect the remainder of this hw region.
			 */
			if ((xstart > start) && (xend < end)) {
				if (acnt > 0 &&
				    avail[acnt - 1] == (vm_paddr_t)start) {
					avail[acnt - 1] = (vm_paddr_t)xstart;
				} else {
					avail[acnt++] = (vm_paddr_t)start;
					avail[acnt++] = (vm_paddr_t)xstart;
				}
				availmem +=
				    pm_btop((vm_offset_t)(xstart - start));
				start = xend;
				continue;
			}
			/*
			 * We know the excluded region overlaps either the start
			 * or end of this hardware region (but not both), trim
			 * the excluded portion off the appropriate end.
			 */
			if (xstart <= start)
				start = xend;
			else
				end = xstart;
		}
		/*
		 * If the trimming actions above left a non-zero size, create an
		 * available entry for it.
		 */
		if (end > start) {
			if (acnt > 0 && avail[acnt - 1] == (vm_paddr_t)start) {
				avail[acnt - 1] = (vm_paddr_t)end;
			} else {
				avail[acnt++] = (vm_paddr_t)start;
				avail[acnt++] = (vm_paddr_t)end;
			}
			availmem += pm_btop((vm_offset_t)(end - start));
		}
		if (acnt >= maxavail)
			panic("Not enough space in the dump/phys_avail arrays");
	}

	if (pavail != NULL)
		*pavail = availmem;
	if (prealmem != NULL)
		*prealmem = totalmem;
	return (acnt);
}