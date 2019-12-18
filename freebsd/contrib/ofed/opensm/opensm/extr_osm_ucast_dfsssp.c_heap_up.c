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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  binary_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_exchange (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ heap_smaller (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static uint32_t heap_up(binary_heap_t * heap, uint32_t i)
{
	uint32_t curr = i, father = 0;

	if (curr > 0) {
		father = (curr - 1) >> 1;
		while (heap_smaller(heap, curr, father)) {
			heap_exchange(heap, curr, father);
			/* try to go up when we arent already root */
			curr = father;
			if (curr > 0)
				father = (curr - 1) >> 1;
		}
	}

	return curr;
}