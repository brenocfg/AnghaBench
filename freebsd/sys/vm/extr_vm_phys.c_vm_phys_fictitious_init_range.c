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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct TYPE_5__ {int /*<<< orphan*/  busy_lock; int /*<<< orphan*/  oflags; } ;

/* Variables and functions */
 long PAGE_SIZE ; 
 int /*<<< orphan*/  VPB_UNBUSIED ; 
 int /*<<< orphan*/  VPO_UNMANAGED ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,long) ; 
 int /*<<< orphan*/  vm_page_initfake (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vm_phys_fictitious_init_range(vm_page_t range, vm_paddr_t start,
    long page_count, vm_memattr_t memattr)
{
	long i;

	bzero(range, page_count * sizeof(*range));
	for (i = 0; i < page_count; i++) {
		vm_page_initfake(&range[i], start + PAGE_SIZE * i, memattr);
		range[i].oflags &= ~VPO_UNMANAGED;
		range[i].busy_lock = VPB_UNBUSIED;
	}
}