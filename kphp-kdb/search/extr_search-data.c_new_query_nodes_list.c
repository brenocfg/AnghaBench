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
struct query_nodes_list {scalar_t__ next; int /*<<< orphan*/ * v; } ;
typedef  int /*<<< orphan*/  query_node_t ;

/* Variables and functions */
 scalar_t__ MAX_QUERY_NODES ; 
 int /*<<< orphan*/  assert (int) ; 
 struct query_nodes_list* query_nodes_list_buffer ; 
 scalar_t__ tot_query_nodes_list ; 

__attribute__((used)) static struct query_nodes_list *new_query_nodes_list (query_node_t *X) {
  assert (tot_query_nodes_list < MAX_QUERY_NODES);
  struct query_nodes_list *p = &query_nodes_list_buffer[tot_query_nodes_list++];
  p->v = X;
  p->next = 0;
  return p;
}