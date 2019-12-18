#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t heap_id; } ;
typedef  TYPE_1__ vertex_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {TYPE_1__** nodes; } ;
typedef  TYPE_2__ binary_heap_t ;

/* Variables and functions */

__attribute__((used)) static void heap_exchange(binary_heap_t * heap, uint32_t i, uint32_t j)
{
	uint32_t tmp_heap_id = 0;
	vertex_t *tmp_node = NULL;

	/* 1. swap the heap_id */
	tmp_heap_id = heap->nodes[i]->heap_id;
	heap->nodes[i]->heap_id = heap->nodes[j]->heap_id;
	heap->nodes[j]->heap_id = tmp_heap_id;
	/* 2. swap pointers */
	tmp_node = heap->nodes[i];
	heap->nodes[i] = heap->nodes[j];
	heap->nodes[j] = tmp_node;
}