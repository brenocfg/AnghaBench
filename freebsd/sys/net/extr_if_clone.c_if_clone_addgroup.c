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
struct if_clone {int ifc_flags; int /*<<< orphan*/  ifc_name; } ;

/* Variables and functions */
 int IFC_NOGROUP ; 
 int /*<<< orphan*/  IF_CLONE_REMREF (struct if_clone*) ; 
 int /*<<< orphan*/  if_addgroup (struct ifnet*,int /*<<< orphan*/ ) ; 

void
if_clone_addgroup(struct ifnet *ifp, struct if_clone *ifc)
{
	if ((ifc->ifc_flags & IFC_NOGROUP) == 0) {
		if_addgroup(ifp, ifc->ifc_name);
		IF_CLONE_REMREF(ifc);
	}
}