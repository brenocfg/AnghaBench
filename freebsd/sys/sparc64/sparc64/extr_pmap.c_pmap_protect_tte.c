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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_long ;
struct tte {int /*<<< orphan*/  tte_data; } ;
struct pmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (struct pmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_PA (int) ; 
 int TD_PV ; 
 int TD_SW ; 
 int TD_W ; 
 int atomic_clear_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmap_protect_tte(struct pmap *pm, struct pmap *pm2, struct tte *tp,
    vm_offset_t va)
{
	u_long data;
	vm_page_t m;

	PMAP_LOCK_ASSERT(pm, MA_OWNED);
	data = atomic_clear_long(&tp->tte_data, TD_SW | TD_W);
	if ((data & (TD_PV | TD_W)) == (TD_PV | TD_W)) {
		m = PHYS_TO_VM_PAGE(TD_PA(data));
		vm_page_dirty(m);
	}
	return (1);
}