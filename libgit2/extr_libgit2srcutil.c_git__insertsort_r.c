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
typedef  void uint8_t ;
typedef  scalar_t__ (* git__sort_r_cmp ) (void*,void*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (void*) ; 
 void* git__malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void git__insertsort_r(
	void *els, size_t nel, size_t elsize, void *swapel,
	git__sort_r_cmp cmp, void *payload)
{
	uint8_t *base = els;
	uint8_t *end = base + nel * elsize;
	uint8_t *i, *j;
	bool freeswap = !swapel;

	if (freeswap)
		swapel = git__malloc(elsize);

	for (i = base + elsize; i < end; i += elsize)
		for (j = i; j > base && cmp(j, j - elsize, payload) < 0; j -= elsize) {
			memcpy(swapel, j, elsize);
			memcpy(j, j - elsize, elsize);
			memcpy(j - elsize, swapel, elsize);
		}

	if (freeswap)
		git__free(swapel);
}