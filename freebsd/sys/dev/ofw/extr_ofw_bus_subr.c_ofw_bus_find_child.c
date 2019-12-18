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
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_OFWPROP ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 

phandle_t
ofw_bus_find_child(phandle_t start, const char *child_name)
{
	char *name;
	int ret;
	phandle_t child;

	for (child = OF_child(start); child != 0; child = OF_peer(child)) {
		ret = OF_getprop_alloc(child, "name", (void **)&name);
		if (ret == -1)
			continue;
		if (strcmp(name, child_name) == 0) {
			free(name, M_OFWPROP);
			return (child);
		}

		free(name, M_OFWPROP);
	}

	return (0);
}