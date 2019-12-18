#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
struct tte {int tte_data; int /*<<< orphan*/  tte_vpn; } ;
struct TYPE_5__ {scalar_t__ color; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 scalar_t__ DCACHE_COLOR (scalar_t__) ; 
 scalar_t__ DCACHE_COLORS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int TD_8K ; 
 int TD_CP ; 
 int TD_CV ; 
 int TD_PA (scalar_t__) ; 
 int TD_V ; 
 int TD_W ; 
 scalar_t__ TLB_PHYS_TO_DIRECT (scalar_t__) ; 
 int /*<<< orphan*/  TS_8K ; 
 int /*<<< orphan*/  TV_VPN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  critical_enter () ; 
 scalar_t__ dcache_color_ignore ; 
 int /*<<< orphan*/  qmap_addr ; 
 struct tte* tsb_kvtotte (scalar_t__) ; 

vm_offset_t
pmap_quick_enter_page(vm_page_t m)
{
	vm_paddr_t pa;
	vm_offset_t qaddr;
	struct tte *tp;

	pa = VM_PAGE_TO_PHYS(m);
	if (dcache_color_ignore != 0 || m->md.color == DCACHE_COLOR(pa))
		return (TLB_PHYS_TO_DIRECT(pa));

	critical_enter();
	qaddr = PCPU_GET(qmap_addr);
	qaddr += (PAGE_SIZE * ((DCACHE_COLORS + DCACHE_COLOR(pa) -
	    DCACHE_COLOR(qaddr)) % DCACHE_COLORS));
	tp = tsb_kvtotte(qaddr);

	KASSERT(tp->tte_data == 0, ("pmap_quick_enter_page: PTE busy"));
	
	tp->tte_data = TD_V | TD_8K | TD_PA(pa) | TD_CP | TD_CV | TD_W;
	tp->tte_vpn = TV_VPN(qaddr, TS_8K);

	return (qaddr);
}