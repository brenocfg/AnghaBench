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
typedef  int /*<<< orphan*/  cam_pinfo ;

/* Variables and functions */
 scalar_t__ queue_cmp (int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ **,int,int) ; 

__attribute__((used)) static void
heap_down(cam_pinfo **queue_array, int index, int num_entries)
{
	int child;
	int parent;
	
	parent = index;
	child = parent << 1;
	for (; child <= num_entries; child = parent << 1) {

		if (child < num_entries) {
			/* child+1 is the right child of parent */
			if (queue_cmp(queue_array, child + 1, child) < 0)
				child++;
		}
		/* child is now the least child of parent */
		if (queue_cmp(queue_array, parent, child) <= 0)
			break;
		swap(queue_array, child, parent);
		parent = child;
	}
}