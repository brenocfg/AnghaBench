#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t bitmap_t ;
struct TYPE_4__ {size_t nbits; int ngroups; } ;
typedef  TYPE_1__ bitmap_info_t ;

/* Variables and functions */
 size_t BITMAP_GROUP_NBITS ; 
 size_t BITMAP_GROUP_NBITS_MASK ; 
 int /*<<< orphan*/  bitmap_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/  memset (size_t*,int,int /*<<< orphan*/ ) ; 

void
bitmap_init(bitmap_t *bitmap, const bitmap_info_t *binfo, bool fill) {
	size_t extra;

	if (fill) {
		memset(bitmap, 0, bitmap_size(binfo));
		return;
	}

	memset(bitmap, 0xffU, bitmap_size(binfo));
	extra = (BITMAP_GROUP_NBITS - (binfo->nbits & BITMAP_GROUP_NBITS_MASK))
	    & BITMAP_GROUP_NBITS_MASK;
	if (extra != 0) {
		bitmap[binfo->ngroups - 1] >>= extra;
	}
}