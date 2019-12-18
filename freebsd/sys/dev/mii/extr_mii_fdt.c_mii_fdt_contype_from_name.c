#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  mii_contype_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_CONTYPE_UNKNOWN ; 
 TYPE_1__* fdt_contype_names ; 
 size_t nitems (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

mii_contype_t
mii_fdt_contype_from_name(const char *name)
{
	u_int i;

	for (i = 0; i < nitems(fdt_contype_names); ++i) {
		if (strcmp(name, fdt_contype_names[i].name) == 0)
			return (fdt_contype_names[i].type);
	}
	return (MII_CONTYPE_UNKNOWN);
}