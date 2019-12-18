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
 int int_array_len (int const*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int* os_realloc_array (int*,int,int) ; 

void int_array_concat(int **res, const int *a)
{
	int reslen, alen, i;
	int *n;

	reslen = int_array_len(*res);
	alen = int_array_len(a);

	n = os_realloc_array(*res, reslen + alen + 1, sizeof(int));
	if (n == NULL) {
		os_free(*res);
		*res = NULL;
		return;
	}
	for (i = 0; i <= alen; i++)
		n[reslen + i] = a[i];
	*res = n;
}