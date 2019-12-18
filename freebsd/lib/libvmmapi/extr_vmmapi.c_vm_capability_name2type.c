#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* capstrmap ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

int
vm_capability_name2type(const char *capname)
{
	int i;

	for (i = 0; capstrmap[i].name != NULL && capname != NULL; i++) {
		if (strcmp(capstrmap[i].name, capname) == 0)
			return (capstrmap[i].type);
	}

	return (-1);
}