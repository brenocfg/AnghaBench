#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ fielddef_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

fielddef_t *FindField(fielddef_t *defs, char *name)
{
	int i;

	for (i = 0; defs[i].name; i++)
	{
		if (!strcmp(defs[i].name, name)) return &defs[i];
	} //end for
	return NULL;
}