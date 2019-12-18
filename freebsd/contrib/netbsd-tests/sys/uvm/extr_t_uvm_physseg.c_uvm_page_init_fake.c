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
typedef  int /*<<< orphan*/  uvm_physseg_t ;
struct vm_page {int dummy; } ;
typedef  size_t psize_t ;
struct TYPE_2__ {int page_init_done; } ;

/* Variables and functions */
 TYPE_1__ uvm ; 
 size_t uvm_physseg_get_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvm_physseg_get_first () ; 
 int /*<<< orphan*/  uvm_physseg_get_next (int /*<<< orphan*/ ) ; 
 size_t uvm_physseg_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvm_physseg_init_seg (int /*<<< orphan*/ ,struct vm_page*) ; 
 int /*<<< orphan*/  uvm_physseg_seg_alloc_from_slab (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uvm_physseg_seg_chomp_slab (int /*<<< orphan*/ ,struct vm_page*,size_t) ; 
 scalar_t__ uvm_physseg_valid_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uvm_page_init_fake(struct vm_page *pagearray, psize_t pagecount)
{
	uvm_physseg_t bank;
	size_t n;

	for (bank = uvm_physseg_get_first(),
		 uvm_physseg_seg_chomp_slab(bank, pagearray, pagecount);
	     uvm_physseg_valid_p(bank);
	     bank = uvm_physseg_get_next(bank)) {

		n = uvm_physseg_get_end(bank) - uvm_physseg_get_start(bank);
		uvm_physseg_seg_alloc_from_slab(bank, n);
		uvm_physseg_init_seg(bank, pagearray);

		/* set up page array pointers */
		pagearray += n;
		pagecount -= n;
	}

	uvm.page_init_done = true;
}