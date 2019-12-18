#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  free_list; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ range_index_t ;
struct TYPE_7__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  prev; int /*<<< orphan*/ * right; int /*<<< orphan*/  left; void* target_offset; void* limit; void* offset; } ;
typedef  TYPE_2__ range_index_node_t ;
typedef  void* apr_size_t ;

/* Variables and functions */
 TYPE_2__* alloc_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static range_index_node_t *
alloc_range_index_node(range_index_t *ndx,
                       apr_size_t offset,
                       apr_size_t limit,
                       apr_size_t target_offset)
{
  range_index_node_t *const node = alloc_block(ndx->pool, &ndx->free_list);
  node->offset = offset;
  node->limit = limit;
  node->target_offset = target_offset;
  node->left = node->right = NULL;
  node->prev = node->next = NULL;
  return node;
}