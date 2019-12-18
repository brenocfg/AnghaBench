#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int EINVAL ; 
 int _PAGE_CACHE_MASK ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int cachemode2protval (int) ; 
 int /*<<< orphan*/  cattr_name (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  free_memtype (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  is_new_memtype_allowed (unsigned long,unsigned long,int,int) ; 
 scalar_t__ kernel_map_sync_memtype (unsigned long,unsigned long,int) ; 
 int lookup_memtype (unsigned long) ; 
 int /*<<< orphan*/  pat_enabled () ; 
 int pat_pagerange_is_ram (unsigned long,unsigned long) ; 
 int pgprot2cachemode (int /*<<< orphan*/ ) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 
 int reserve_memtype (unsigned long,unsigned long,int,int*) ; 

__attribute__((used)) static int reserve_pfn_range(u64 paddr, unsigned long size, pgprot_t *vma_prot,
				int strict_prot)
{
	int is_ram = 0;
	int ret;
	enum page_cache_mode want_pcm = pgprot2cachemode(*vma_prot);
	enum page_cache_mode pcm = want_pcm;

	is_ram = pat_pagerange_is_ram(paddr, paddr + size);

	/*
	 * reserve_pfn_range() for RAM pages. We do not refcount to keep
	 * track of number of mappings of RAM pages. We can assert that
	 * the type requested matches the type of first page in the range.
	 */
	if (is_ram) {
		if (!pat_enabled())
			return 0;

		pcm = lookup_memtype(paddr);
		if (want_pcm != pcm) {
			pr_warn("x86/PAT: %s:%d map pfn RAM range req %s for [mem %#010Lx-%#010Lx], got %s\n",
				current->comm, current->pid,
				cattr_name(want_pcm),
				(unsigned long long)paddr,
				(unsigned long long)(paddr + size - 1),
				cattr_name(pcm));
			*vma_prot = __pgprot((pgprot_val(*vma_prot) &
					     (~_PAGE_CACHE_MASK)) |
					     cachemode2protval(pcm));
		}
		return 0;
	}

	ret = reserve_memtype(paddr, paddr + size, want_pcm, &pcm);
	if (ret)
		return ret;

	if (pcm != want_pcm) {
		if (strict_prot ||
		    !is_new_memtype_allowed(paddr, size, want_pcm, pcm)) {
			free_memtype(paddr, paddr + size);
			pr_err("x86/PAT: %s:%d map pfn expected mapping type %s for [mem %#010Lx-%#010Lx], got %s\n",
			       current->comm, current->pid,
			       cattr_name(want_pcm),
			       (unsigned long long)paddr,
			       (unsigned long long)(paddr + size - 1),
			       cattr_name(pcm));
			return -EINVAL;
		}
		/*
		 * We allow returning different type than the one requested in
		 * non strict case.
		 */
		*vma_prot = __pgprot((pgprot_val(*vma_prot) &
				      (~_PAGE_CACHE_MASK)) |
				     cachemode2protval(pcm));
	}

	if (kernel_map_sync_memtype(paddr, size, pcm) < 0) {
		free_memtype(paddr, paddr + size);
		return -EINVAL;
	}
	return 0;
}