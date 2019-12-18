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
struct cpa_data {unsigned long* vaddr; int numpages; int /*<<< orphan*/  pgd; void* mask_clr; void* mask_set; } ;
typedef  int /*<<< orphan*/  cpa ;
struct TYPE_2__ {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ WARN_ONCE (unsigned long,char*,unsigned long) ; 
 int /*<<< orphan*/  _PAGE_ENC ; 
 int __change_page_attr_set_clr (struct cpa_data*,int) ; 
 void* __pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpa_flush (struct cpa_data*,int) ; 
 TYPE_1__ init_mm ; 
 int /*<<< orphan*/  kmap_flush_unused () ; 
 int /*<<< orphan*/  mem_encrypt_active () ; 
 int /*<<< orphan*/  memset (struct cpa_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_unmap_aliases () ; 

__attribute__((used)) static int __set_memory_enc_dec(unsigned long addr, int numpages, bool enc)
{
	struct cpa_data cpa;
	int ret;

	/* Nothing to do if memory encryption is not active */
	if (!mem_encrypt_active())
		return 0;

	/* Should not be working on unaligned addresses */
	if (WARN_ONCE(addr & ~PAGE_MASK, "misaligned address: %#lx\n", addr))
		addr &= PAGE_MASK;

	memset(&cpa, 0, sizeof(cpa));
	cpa.vaddr = &addr;
	cpa.numpages = numpages;
	cpa.mask_set = enc ? __pgprot(_PAGE_ENC) : __pgprot(0);
	cpa.mask_clr = enc ? __pgprot(0) : __pgprot(_PAGE_ENC);
	cpa.pgd = init_mm.pgd;

	/* Must avoid aliasing mappings in the highmem code */
	kmap_flush_unused();
	vm_unmap_aliases();

	/*
	 * Before changing the encryption attribute, we need to flush caches.
	 */
	cpa_flush(&cpa, 1);

	ret = __change_page_attr_set_clr(&cpa, 1);

	/*
	 * After changing the encryption attribute, we need to flush TLBs again
	 * in case any speculative TLB caching occurred (but no need to flush
	 * caches again).  We could just use cpa_flush_all(), but in case TLB
	 * flushing gets optimized in the cpa_flush() path use the same logic
	 * as above.
	 */
	cpa_flush(&cpa, 0);

	return ret;
}