#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ rs_end; int /*<<< orphan*/  rs_start; } ;
typedef  TYPE_1__ range_seg_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 TYPE_1__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ P2ROUNDUP (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* metaslab_block_find (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint64_t
metaslab_block_picker(avl_tree_t *t, uint64_t *cursor, uint64_t size,
    uint64_t align)
{
	range_seg_t *rs = metaslab_block_find(t, *cursor, size);

	while (rs != NULL) {
		uint64_t offset = P2ROUNDUP(rs->rs_start, align);

		if (offset + size <= rs->rs_end) {
			*cursor = offset + size;
			return (offset);
		}
		rs = AVL_NEXT(t, rs);
	}

	/*
	 * If we know we've searched the whole map (*cursor == 0), give up.
	 * Otherwise, reset the cursor to the beginning and try again.
	 */
	if (*cursor == 0)
		return (-1ULL);

	*cursor = 0;
	return (metaslab_block_picker(t, cursor, size, align));
}