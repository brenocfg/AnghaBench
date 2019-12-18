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
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct ntb_child {unsigned int mwoff; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int NTB_MW_SET_WC (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

int
ntb_mw_set_wc(device_t ntb, unsigned mw_idx, vm_memattr_t mode)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	return (NTB_MW_SET_WC(device_get_parent(ntb), mw_idx + nc->mwoff, mode));
}