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
struct ixl_vsi {int num_vlans; int /*<<< orphan*/  num_macs; struct ixl_pf* back; } ;
struct ixl_pf {int /*<<< orphan*/  dev; } ;
struct ixl_mac_filter {scalar_t__ vlan; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ s16 ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXL_FILTER_USED ; 
 int /*<<< orphan*/  IXL_FILTER_VLAN ; 
 scalar_t__ IXL_VLAN_ANY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixl_add_hw_filters (struct ixl_vsi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixl_del_filter (struct ixl_vsi*,int /*<<< orphan*/  const*,scalar_t__) ; 
 struct ixl_mac_filter* ixl_find_filter (struct ixl_vsi*,int /*<<< orphan*/  const*,scalar_t__) ; 
 struct ixl_mac_filter* ixl_new_filter (struct ixl_vsi*,int /*<<< orphan*/  const*,scalar_t__) ; 

void
ixl_add_filter(struct ixl_vsi *vsi, const u8 *macaddr, s16 vlan)
{
	struct ixl_mac_filter	*f, *tmp;
	struct ixl_pf		*pf;
	device_t		dev;

	DEBUGOUT("ixl_add_filter: begin");

	pf = vsi->back;
	dev = pf->dev;

	/* Does one already exist */
	f = ixl_find_filter(vsi, macaddr, vlan);
	if (f != NULL)
		return;
	/*
	** Is this the first vlan being registered, if so we
	** need to remove the ANY filter that indicates we are
	** not in a vlan, and replace that with a 0 filter.
	*/
	if ((vlan != IXL_VLAN_ANY) && (vsi->num_vlans == 1)) {
		tmp = ixl_find_filter(vsi, macaddr, IXL_VLAN_ANY);
		if (tmp != NULL) {
			ixl_del_filter(vsi, macaddr, IXL_VLAN_ANY);
			ixl_add_filter(vsi, macaddr, 0);
		}
	}

	f = ixl_new_filter(vsi, macaddr, vlan);
	if (f == NULL) {
		device_printf(dev, "WARNING: no filter available!!\n");
		return;
	}
	if (f->vlan != IXL_VLAN_ANY)
		f->flags |= IXL_FILTER_VLAN;
	else
		vsi->num_macs++;

	f->flags |= IXL_FILTER_USED;
	ixl_add_hw_filters(vsi, f->flags, 1);
}