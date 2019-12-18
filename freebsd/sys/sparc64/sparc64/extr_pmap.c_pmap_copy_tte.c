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
struct tte {int tte_data; } ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int TD_CV ; 
 int TD_FAKE ; 
 int TD_PV ; 
 int TD_REF ; 
 int TD_SW ; 
 int TD_W ; 
 int /*<<< orphan*/  TS_8K ; 
 int /*<<< orphan*/  TTE_GET_PA (struct tte*) ; 
 int /*<<< orphan*/  tsb_tte_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * tsb_tte_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmap_copy_tte(pmap_t src_pmap, pmap_t dst_pmap, struct tte *tp,
    vm_offset_t va)
{
	vm_page_t m;
	u_long data;

	if ((tp->tte_data & TD_FAKE) != 0)
		return (1);
	if (tsb_tte_lookup(dst_pmap, va) == NULL) {
		data = tp->tte_data &
		    ~(TD_PV | TD_REF | TD_SW | TD_CV | TD_W);
		m = PHYS_TO_VM_PAGE(TTE_GET_PA(tp));
		tsb_tte_enter(dst_pmap, m, va, TS_8K, data);
	}
	return (1);
}