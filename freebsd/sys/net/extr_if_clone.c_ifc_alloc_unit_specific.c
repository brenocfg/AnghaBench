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
struct if_clone {int ifc_maxunit; char* ifc_name; int /*<<< orphan*/  ifc_unrhdr; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOSPC ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  IF_CLONE_ADDREF (struct if_clone*) ; 
 int alloc_unr_specific (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ifunit (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int
ifc_alloc_unit_specific(struct if_clone *ifc, int *unit)
{
	char name[IFNAMSIZ];

	if (*unit > ifc->ifc_maxunit)
		return (ENOSPC);

	if (alloc_unr_specific(ifc->ifc_unrhdr, *unit) == -1)
		return (EEXIST);

	snprintf(name, IFNAMSIZ, "%s%d", ifc->ifc_name, *unit);
	if (ifunit(name) != NULL) {
		free_unr(ifc->ifc_unrhdr, *unit);
		return (EEXIST);
	}

	IF_CLONE_ADDREF(ifc);

	return (0);
}