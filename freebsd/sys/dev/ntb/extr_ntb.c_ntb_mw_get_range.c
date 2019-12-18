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
struct ntb_child {unsigned int mwoff; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int NTB_MW_GET_RANGE (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

int
ntb_mw_get_range(device_t ntb, unsigned mw_idx, vm_paddr_t *base,
    caddr_t *vbase, size_t *size, size_t *align, size_t *align_size,
    bus_addr_t *plimit)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	return (NTB_MW_GET_RANGE(device_get_parent(ntb), mw_idx + nc->mwoff,
	    base, vbase, size, align, align_size, plimit));
}