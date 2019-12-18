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
typedef  scalar_t__ (* git__sort_r_cmp ) (void*,void*,void*) ;

/* Variables and functions */
 int binsearch (void**,void*,size_t,scalar_t__ (*) (void*,void*,void*),void*) ; 

__attribute__((used)) static void bisort(
	void **dst, size_t start, size_t size, git__sort_r_cmp cmp, void *payload)
{
	size_t i;
	void *x;
	int location;

	for (i = start; i < size; i++) {
		int j;
		/* If this entry is already correct, just move along */
		if (cmp(dst[i - 1], dst[i], payload) <= 0)
			continue;

		/* Else we need to find the right place, shift everything over, and squeeze in */
		x = dst[i];
		location = binsearch(dst, x, i, cmp, payload);
		for (j = (int)i - 1; j >= location; j--) {
			dst[j + 1] = dst[j];
		}
		dst[location] = x;
	}
}