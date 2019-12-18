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
struct ibv_mem_node {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mm_remove (struct ibv_mem_node*) ; 

__attribute__((used)) static struct ibv_mem_node *merge_ranges(struct ibv_mem_node *node,
					 struct ibv_mem_node *prev)
{
	prev->end = node->end;
	prev->refcnt = node->refcnt;
	__mm_remove(node);

	return prev;
}