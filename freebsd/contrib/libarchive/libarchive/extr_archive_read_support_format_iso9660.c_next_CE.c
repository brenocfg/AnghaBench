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
typedef  scalar_t__ uint64_t ;
struct read_ce_req {scalar_t__ offset; } ;
struct read_ce_queue {int cnt; struct read_ce_req* reqs; } ;

/* Variables and functions */

__attribute__((used)) static void
next_CE(struct read_ce_queue *heap)
{
	uint64_t a_offset, b_offset, c_offset;
	int a, b, c;
	struct read_ce_req tmp;

	if (heap->cnt < 1)
		return;

	/*
	 * Move the last item in the heap to the root of the tree
	 */
	heap->reqs[0] = heap->reqs[--(heap->cnt)];

	/*
	 * Rebalance the heap.
	 */
	a = 0; /* Starting element and its offset */
	a_offset = heap->reqs[a].offset;
	for (;;) {
		b = a + a + 1; /* First child */
		if (b >= heap->cnt)
			return;
		b_offset = heap->reqs[b].offset;
		c = b + 1; /* Use second child if it is smaller. */
		if (c < heap->cnt) {
			c_offset = heap->reqs[c].offset;
			if (c_offset < b_offset) {
				b = c;
				b_offset = c_offset;
			}
		}
		if (a_offset <= b_offset)
			return;
		tmp = heap->reqs[a];
		heap->reqs[a] = heap->reqs[b];
		heap->reqs[b] = tmp;
		a = b;
	}
}