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
typedef  unsigned long uint8_t ;
typedef  unsigned int u_long ;
struct kvm_bitmap {unsigned long* map; } ;

/* Variables and functions */

void
_kvm_bitmap_set(struct kvm_bitmap *bm, u_long pa, unsigned int page_size)
{
	u_long bm_index = pa / page_size;
	uint8_t *byte = &bm->map[bm_index / 8];

	*byte |= (1UL << (bm_index % 8));
}