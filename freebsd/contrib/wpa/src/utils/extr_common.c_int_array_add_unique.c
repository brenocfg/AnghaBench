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

/* Variables and functions */
 int /*<<< orphan*/  os_free (int*) ; 
 int* os_realloc_array (int*,int,int) ; 

void int_array_add_unique(int **res, int a)
{
	int reslen;
	int *n;

	for (reslen = 0; *res && (*res)[reslen]; reslen++) {
		if ((*res)[reslen] == a)
			return; /* already in the list */
	}

	n = os_realloc_array(*res, reslen + 2, sizeof(int));
	if (n == NULL) {
		os_free(*res);
		*res = NULL;
		return;
	}

	n[reslen] = a;
	n[reslen + 1] = 0;

	*res = n;
}