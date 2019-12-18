#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct vm_freelist {int dummy; } ;
struct TYPE_4__ {scalar_t__ order; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ VM_NFREEORDER ; 
 int /*<<< orphan*/  vm_freelist_add (struct vm_freelist*,TYPE_1__*,int,int) ; 

__attribute__((used)) static __inline void
vm_phys_split_pages(vm_page_t m, int oind, struct vm_freelist *fl, int order,
    int tail)
{
	vm_page_t m_buddy;

	while (oind > order) {
		oind--;
		m_buddy = &m[1 << oind];
		KASSERT(m_buddy->order == VM_NFREEORDER,
		    ("vm_phys_split_pages: page %p has unexpected order %d",
		    m_buddy, m_buddy->order));
		vm_freelist_add(fl, m_buddy, oind, tail);
        }
}