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
 int GIT_ENOTFOUND ; 
 int stub1 (void const*,void const*,void*) ; 

int git__bsearch_r(
	void **array,
	size_t array_len,
	const void *key,
	int (*compare_r)(const void *, const void *, void *),
	void *payload,
	size_t *position)
{
	size_t lim;
	int cmp = -1;
	void **part, **base = array;

	for (lim = array_len; lim != 0; lim >>= 1) {
		part = base + (lim >> 1);
		cmp = (*compare_r)(key, *part, payload);
		if (cmp == 0) {
			base = part;
			break;
		}
		if (cmp > 0) { /* key > p; take right partition */
			base = part + 1;
			lim--;
		} /* else take left partition */
	}

	if (position)
		*position = (base - array);

	return (cmp == 0) ? 0 : GIT_ENOTFOUND;
}