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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_long ;
struct tte {int tte_data; int /*<<< orphan*/  tte_vpn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tte*,int) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int TD_8K ; 
 int TD_P ; 
 int TD_PA (int /*<<< orphan*/ ) ; 
 int TD_REF ; 
 int TD_V ; 
 int /*<<< orphan*/  TS_8K ; 
 int /*<<< orphan*/  TV_VPN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tte* tsb_kvtotte (int /*<<< orphan*/ ) ; 

void
pmap_kenter_flags(vm_offset_t va, vm_paddr_t pa, u_long flags)
{
	struct tte *tp;

	tp = tsb_kvtotte(va);
	CTR4(KTR_PMAP, "pmap_kenter_flags: va=%#lx pa=%#lx tp=%p data=%#lx",
	    va, pa, tp, tp->tte_data);
	tp->tte_vpn = TV_VPN(va, TS_8K);
	tp->tte_data = TD_V | TD_8K | TD_PA(pa) | TD_REF | TD_P | flags;
}