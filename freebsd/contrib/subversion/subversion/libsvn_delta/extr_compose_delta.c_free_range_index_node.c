#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  free_list; } ;
typedef  TYPE_3__ range_index_t ;
struct TYPE_11__ {TYPE_2__* next; TYPE_1__* prev; } ;
typedef  TYPE_4__ range_index_node_t ;
struct TYPE_9__ {TYPE_1__* prev; } ;
struct TYPE_8__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_block (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_range_index_node(range_index_t *ndx, range_index_node_t *node)
{
  if (node->next)
    node->next->prev = node->prev;
  if (node->prev)
    node->prev->next = node->next;
  free_block(node, &ndx->free_list);
}