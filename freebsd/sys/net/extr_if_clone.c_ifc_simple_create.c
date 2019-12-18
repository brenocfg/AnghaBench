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
struct if_clone {int (* ifcs_create ) (struct if_clone*,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ifc_alloc_unit (struct if_clone*,int*) ; 
 int /*<<< orphan*/  ifc_free_unit (struct if_clone*,int) ; 
 int ifc_name2unit (char*,int*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 size_t snprintf (char*,size_t,char*,int) ; 
 int stub1 (struct if_clone*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ifc_simple_create(struct if_clone *ifc, char *name, size_t len, caddr_t params)
{
	char *dp;
	int wildcard;
	int unit;
	int err;

	err = ifc_name2unit(name, &unit);
	if (err != 0)
		return (err);

	wildcard = (unit < 0);

	err = ifc_alloc_unit(ifc, &unit);
	if (err != 0)
		return (err);

	err = ifc->ifcs_create(ifc, unit, params);
	if (err != 0) {
		ifc_free_unit(ifc, unit);
		return (err);
	}

	/* In the wildcard case, we need to update the name. */
	if (wildcard) {
		for (dp = name; *dp != '\0'; dp++);
		if (snprintf(dp, len - (dp-name), "%d", unit) >
		    len - (dp-name) - 1) {
			/*
			 * This can only be a programmer error and
			 * there's no straightforward way to recover if
			 * it happens.
			 */
			panic("if_clone_create(): interface name too long");
		}

	}

	return (0);
}