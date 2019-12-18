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
typedef  scalar_t__ u_long ;
struct kvm_bitmap {scalar_t__ size; unsigned int* map; } ;

/* Variables and functions */
 scalar_t__ CHAR_BIT ; 
 scalar_t__ ULONG_MAX ; 

int
_kvm_bitmap_next(struct kvm_bitmap *bm, u_long *idx)
{
	u_long first_invalid = bm->size * CHAR_BIT;

	if (*idx == ULONG_MAX)
		*idx = 0;
	else
		(*idx)++;

	/* Find the next valid idx. */
	for (; *idx < first_invalid; (*idx)++) {
		unsigned int mask = *idx % CHAR_BIT;
		if ((bm->map[*idx * CHAR_BIT] & mask) == 0)
			break;
	}

	return (*idx < first_invalid);
}