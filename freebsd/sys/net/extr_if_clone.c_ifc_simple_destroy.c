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
struct ifnet {int if_dunit; } ;
struct if_clone {int ifcs_minifs; int /*<<< orphan*/  (* ifcs_destroy ) (struct ifnet*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ifc_free_unit (struct if_clone*,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 

__attribute__((used)) static int
ifc_simple_destroy(struct if_clone *ifc, struct ifnet *ifp)
{
	int unit;

	unit = ifp->if_dunit;

	if (unit < ifc->ifcs_minifs) 
		return (EINVAL);

	ifc->ifcs_destroy(ifp);

	ifc_free_unit(ifc, unit);

	return (0);
}