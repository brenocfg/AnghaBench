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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,void*) ; 
 int /*<<< orphan*/ * range_tree_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
range_tree_verify(range_tree_t *rt, uint64_t off, uint64_t size)
{
	range_seg_t *rs;

	rs = range_tree_find(rt, off, size);
	if (rs != NULL)
		panic("freeing free block; rs=%p", (void *)rs);
}