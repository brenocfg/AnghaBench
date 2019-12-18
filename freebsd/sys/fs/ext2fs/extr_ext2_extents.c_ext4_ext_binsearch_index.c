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
struct ext4_extent_path {struct ext4_extent_index* ep_index; struct ext4_extent_header* ep_header; } ;
struct ext4_extent_index {int ei_blk; } ;
struct ext4_extent_header {scalar_t__ eh_ecount; scalar_t__ eh_max; } ;

/* Variables and functions */
 struct ext4_extent_index* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static void
ext4_ext_binsearch_index(struct ext4_extent_path *path, int blk)
{
	struct ext4_extent_header *eh;
	struct ext4_extent_index *r, *l, *m;

	eh = path->ep_header;

	KASSERT(eh->eh_ecount <= eh->eh_max && eh->eh_ecount > 0,
	    ("ext4_ext_binsearch_index: bad args"));

	l = EXT_FIRST_INDEX(eh) + 1;
	r = EXT_FIRST_INDEX(eh) + eh->eh_ecount - 1;
	while (l <= r) {
		m = l + (r - l) / 2;
		if (blk < m->ei_blk)
			r = m - 1;
		else
			l = m + 1;
	}

	path->ep_index = l - 1;
}