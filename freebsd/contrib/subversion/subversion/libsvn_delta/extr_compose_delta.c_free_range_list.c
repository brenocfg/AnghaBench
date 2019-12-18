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
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ range_list_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  free_list; } ;
typedef  TYPE_2__ range_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_block (TYPE_1__* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_range_list(range_list_node_t *list, range_index_t *ndx)
{
  while (list)
    {
      range_list_node_t *const node = list;
      list = node->next;
      free_block(node, &ndx->free_list);
    }
}