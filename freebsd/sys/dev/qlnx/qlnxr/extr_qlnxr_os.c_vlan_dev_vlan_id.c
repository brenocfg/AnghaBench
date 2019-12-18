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
typedef  int /*<<< orphan*/  uint16_t ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ VLAN_TAG (struct ifnet*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint16_t
vlan_dev_vlan_id(struct ifnet *ifp)
{
	uint16_t vtag;

	if (VLAN_TAG(ifp, &vtag) == 0)
		return (vtag);

	return (0);
}