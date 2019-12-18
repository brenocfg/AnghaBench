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

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PMD_MASK ; 
 int /*<<< orphan*/  sh64_dcache_purge_all () ; 
 int /*<<< orphan*/  sh64_dcache_purge_user_pages (struct mm_struct*,unsigned long,unsigned long) ; 

__attribute__((used)) static void sh64_dcache_purge_user_range(struct mm_struct *mm,
			  unsigned long start, unsigned long end)
{
	int n_pages = ((end - start) >> PAGE_SHIFT);

	if (n_pages >= 64 || ((start ^ (end - 1)) & PMD_MASK)) {
		sh64_dcache_purge_all();
	} else {
		/* Small range, covered by a single page table page */
		start &= PAGE_MASK;	/* should already be so */
		end = PAGE_ALIGN(end);	/* should already be so */
		sh64_dcache_purge_user_pages(mm, start, end);
	}
}