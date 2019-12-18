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
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char const*,void**) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 

int
ofw_bus_find_string_index(phandle_t node, const char *list_name,
    const char *name, int *idx)
{
	char *elems;
	int rv, i, cnt, nelems;

	elems = NULL;
	nelems = OF_getprop_alloc(node, list_name, (void **)&elems);
	if (nelems <= 0)
		return (ENOENT);

	rv = ENOENT;
	for (i = 0, cnt = 0; i < nelems; cnt++) {
		if (strcmp(elems + i, name) == 0) {
			*idx = cnt;
			rv = 0;
			break;
		}
		i += strlen(elems + i) + 1;
	}

	if (elems != NULL)
		free(elems, M_OFWPROP);
	return (rv);
}