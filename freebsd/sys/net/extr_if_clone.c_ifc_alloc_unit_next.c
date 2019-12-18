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
struct if_clone {int /*<<< orphan*/  ifc_unrhdr; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOSPC ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int ifc_alloc_unit_specific (struct if_clone*,int*) ; 

__attribute__((used)) static int
ifc_alloc_unit_next(struct if_clone *ifc, int *unit)
{
	int error;

	*unit = alloc_unr(ifc->ifc_unrhdr);
	if (*unit == -1)
		return (ENOSPC);

	free_unr(ifc->ifc_unrhdr, *unit);
	for (;;) {
		error = ifc_alloc_unit_specific(ifc, unit);
		if (error != EEXIST)
			break;

		(*unit)++;
	}

	return (error);
}