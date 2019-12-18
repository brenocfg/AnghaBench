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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLAN_XLOCK () ; 
 int /*<<< orphan*/  VLAN_XUNLOCK () ; 
 int /*<<< orphan*/  vlan_unconfig_locked (struct ifnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlan_unconfig(struct ifnet *ifp)
{

	VLAN_XLOCK();
	vlan_unconfig_locked(ifp, 0);
	VLAN_XUNLOCK();
}