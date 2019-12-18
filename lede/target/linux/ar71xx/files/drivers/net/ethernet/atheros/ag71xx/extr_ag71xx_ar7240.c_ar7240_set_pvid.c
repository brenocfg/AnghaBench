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
struct switch_dev {int vlans; } ;
struct ar7240sw {int* pvid; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ar7240sw* sw_to_ar7240 (struct switch_dev*) ; 

__attribute__((used)) static int
ar7240_set_pvid(struct switch_dev *dev, int port, int vlan)
{
	struct ar7240sw *as = sw_to_ar7240(dev);

	/* make sure no invalid PVIDs get set */

	if (vlan >= dev->vlans)
		return -EINVAL;

	as->pvid[port] = vlan;
	return 0;
}