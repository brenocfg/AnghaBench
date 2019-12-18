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
struct if_clone {scalar_t__ ifc_type; int /*<<< orphan*/  ifc_iflist; scalar_t__ ifcs_minifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_CLONERS_LOCK () ; 
 int /*<<< orphan*/  IF_CLONERS_UNLOCK () ; 
 int /*<<< orphan*/  IF_CLONE_REMREF (struct if_clone*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct if_clone*,int /*<<< orphan*/ ) ; 
 scalar_t__ SIMPLE ; 
 int /*<<< orphan*/  V_if_cloners_count ; 
 int /*<<< orphan*/  if_clone_destroyif (struct if_clone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifc_list ; 

void
if_clone_detach(struct if_clone *ifc)
{

	IF_CLONERS_LOCK();
	LIST_REMOVE(ifc, ifc_list);
	V_if_cloners_count--;
	IF_CLONERS_UNLOCK();

	/* Allow all simples to be destroyed */
	if (ifc->ifc_type == SIMPLE)
		ifc->ifcs_minifs = 0;

	/* destroy all interfaces for this cloner */
	while (!LIST_EMPTY(&ifc->ifc_iflist))
		if_clone_destroyif(ifc, LIST_FIRST(&ifc->ifc_iflist));

	IF_CLONE_REMREF(ifc);
}