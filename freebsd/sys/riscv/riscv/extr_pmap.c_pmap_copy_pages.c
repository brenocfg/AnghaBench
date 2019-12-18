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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  size_t vm_offset_t ;
struct TYPE_4__ {int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 size_t PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_IN_DMAP (int /*<<< orphan*/ ) ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

void
pmap_copy_pages(vm_page_t ma[], vm_offset_t a_offset, vm_page_t mb[],
    vm_offset_t b_offset, int xfersize)
{
	void *a_cp, *b_cp;
	vm_page_t m_a, m_b;
	vm_paddr_t p_a, p_b;
	vm_offset_t a_pg_offset, b_pg_offset;
	int cnt;

	while (xfersize > 0) {
		a_pg_offset = a_offset & PAGE_MASK;
		m_a = ma[a_offset >> PAGE_SHIFT];
		p_a = m_a->phys_addr;
		b_pg_offset = b_offset & PAGE_MASK;
		m_b = mb[b_offset >> PAGE_SHIFT];
		p_b = m_b->phys_addr;
		cnt = min(xfersize, PAGE_SIZE - a_pg_offset);
		cnt = min(cnt, PAGE_SIZE - b_pg_offset);
		if (__predict_false(!PHYS_IN_DMAP(p_a))) {
			panic("!DMAP a %lx", p_a);
		} else {
			a_cp = (char *)PHYS_TO_DMAP(p_a) + a_pg_offset;
		}
		if (__predict_false(!PHYS_IN_DMAP(p_b))) {
			panic("!DMAP b %lx", p_b);
		} else {
			b_cp = (char *)PHYS_TO_DMAP(p_b) + b_pg_offset;
		}
		bcopy(a_cp, b_cp, cnt);
		a_offset += cnt;
		b_offset += cnt;
		xfersize -= cnt;
	}
}