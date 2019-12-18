#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int kind; struct TYPE_8__* next; struct TYPE_8__* prev; void* target_offset; void* limit; void* offset; } ;
typedef  TYPE_1__ range_list_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  free_list; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ range_index_t ;
typedef  enum range_kind { ____Placeholder_range_kind } range_kind ;
typedef  void* apr_size_t ;

/* Variables and functions */
 TYPE_1__* alloc_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static range_list_node_t *
alloc_range_list(range_list_node_t **list,
                 range_list_node_t **tail,
                 range_index_t *ndx,
                 enum range_kind kind,
                 apr_size_t offset,
                 apr_size_t limit,
                 apr_size_t target_offset)
{
  range_list_node_t *const node = alloc_block(ndx->pool, &ndx->free_list);
  node->kind = kind;
  node->offset = offset;
  node->limit = limit;
  node->target_offset = target_offset;
  if (*list == NULL)
    {
      node->prev = node->next = NULL;
      *list = *tail = node;
    }
  else
    {
      node->prev = *tail;
      node->next = NULL;
      (*tail)->next = node;
      *tail = node;
    }
  return *list;
}