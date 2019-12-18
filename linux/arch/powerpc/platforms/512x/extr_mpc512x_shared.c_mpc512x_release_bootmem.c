#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * release_bootmem; } ;
struct TYPE_3__ {unsigned long fb_phys; unsigned long fb_len; int in_use; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PFN_DOWN (unsigned long) ; 
 unsigned long PFN_UP (unsigned long) ; 
 TYPE_2__ diu_ops ; 
 TYPE_1__ diu_shared_fb ; 
 int /*<<< orphan*/  mpc512x_free_bootmem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 

__attribute__((used)) static void mpc512x_release_bootmem(void)
{
	unsigned long addr = diu_shared_fb.fb_phys & PAGE_MASK;
	unsigned long size = diu_shared_fb.fb_len;
	unsigned long start, end;

	if (diu_shared_fb.in_use) {
		start = PFN_UP(addr);
		end = PFN_DOWN(addr + size);

		for (; start < end; start++)
			mpc512x_free_bootmem(pfn_to_page(start));

		diu_shared_fb.in_use = false;
	}
	diu_ops.release_bootmem	= NULL;
}