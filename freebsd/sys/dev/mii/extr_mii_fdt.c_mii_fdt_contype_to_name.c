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
typedef  scalar_t__ mii_contype_t ;
struct TYPE_3__ {scalar_t__ type; char const* name; } ;

/* Variables and functions */
 TYPE_1__* fdt_contype_names ; 
 size_t nitems (TYPE_1__*) ; 

const char *
mii_fdt_contype_to_name(mii_contype_t contype)
{
	u_int i;

	for (i = 0; i < nitems(fdt_contype_names); ++i) {
		if (contype == fdt_contype_names[i].type)
			return (fdt_contype_names[i].name);
	}
	return (fdt_contype_names[0].name);
}