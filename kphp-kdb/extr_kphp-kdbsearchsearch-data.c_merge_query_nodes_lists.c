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
struct query_nodes_list {struct query_nodes_list* next; } ;

/* Variables and functions */

__attribute__((used)) static void merge_query_nodes_lists (struct query_nodes_list *p, struct query_nodes_list *q) {
  while (p->next) {
    p = p->next;
  }
  p->next = q;
}