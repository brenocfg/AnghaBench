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
 int /*<<< orphan*/  IF_CLONE_REMREF (struct if_clone*) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 

void
ifc_free_unit(struct if_clone *ifc, int unit)
{

	free_unr(ifc->ifc_unrhdr, unit);
	IF_CLONE_REMREF(ifc);
}