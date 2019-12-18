#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* treap_node_ptr ;
struct TYPE_5__ {struct TYPE_5__* l; } ;
typedef  TYPE_1__ treap_node ;

/* Variables and functions */
 int allocated_nodes_cnt ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* free_nodes ; 
 scalar_t__ free_nodes_cnt ; 
 int /*<<< orphan*/  treap_init_mem (int) ; 

treap_node *get_new_node (void) {
  if (free_nodes_cnt == 0) {
    if (allocated_nodes_cnt < 10000) {
      if (allocated_nodes_cnt < 10) {
        treap_init_mem (10);
      } else {
        treap_init_mem (allocated_nodes_cnt);
      }
    } else {
      treap_init_mem (10000);
    }
  }

  free_nodes_cnt--;
  assert (free_nodes_cnt >= 0);

  treap_node_ptr res = free_nodes;
  free_nodes = free_nodes->l;
  res->l = NULL;

  return res;
}