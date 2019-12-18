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
typedef  int /*<<< orphan*/  u8 ;
struct ixl_vsi {int dummy; } ;
struct ixl_mac_filter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXL_FILTER_MC ; 
 int /*<<< orphan*/  IXL_VLAN_ANY ; 
 struct ixl_mac_filter* ixl_find_filter (struct ixl_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ixl_mac_filter* ixl_new_filter (struct ixl_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
ixl_add_mc_filter(struct ixl_vsi *vsi, u8 *macaddr)
{
	struct ixl_mac_filter *f;

	/* Does one already exist */
	f = ixl_find_filter(vsi, macaddr, IXL_VLAN_ANY);
	if (f != NULL)
		return;

	f = ixl_new_filter(vsi, macaddr, IXL_VLAN_ANY);
	if (f != NULL)
		f->flags |= IXL_FILTER_MC;
	else
		printf("WARNING: no filter available!!\n");
}