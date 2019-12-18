#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_page_bits_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int valid; } ;

/* Variables and functions */
 int DEV_BSHIFT ; 
 int DEV_BSIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  pmap_zero_page_area (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vm_page_valid (TYPE_1__*) ; 

void
vm_page_zero_invalid(vm_page_t m, boolean_t setvalid)
{
	int b;
	int i;

	/*
	 * Scan the valid bits looking for invalid sections that
	 * must be zeroed.  Invalid sub-DEV_BSIZE'd areas ( where the
	 * valid bit may be set ) have already been zeroed by
	 * vm_page_set_validclean().
	 */
	for (b = i = 0; i <= PAGE_SIZE / DEV_BSIZE; ++i) {
		if (i == (PAGE_SIZE / DEV_BSIZE) ||
		    (m->valid & ((vm_page_bits_t)1 << i))) {
			if (i > b) {
				pmap_zero_page_area(m,
				    b << DEV_BSHIFT, (i - b) << DEV_BSHIFT);
			}
			b = i + 1;
		}
	}

	/*
	 * setvalid is TRUE when we can safely set the zero'd areas
	 * as being valid.  We can do this if there are no cache consistancy
	 * issues.  e.g. it is ok to do with UFS, but not ok to do with NFS.
	 */
	if (setvalid)
		vm_page_valid(m);
}