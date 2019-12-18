#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* trp_node_ptr ;
struct TYPE_4__ {struct TYPE_4__* l; struct TYPE_4__* r; } ;

/* Variables and functions */
 TYPE_1__* free_nodes ; 
 int /*<<< orphan*/  free_nodes_cnt ; 

void trp_free (trp_node_ptr v) {
  if (v == NULL) {
    return;
  }
  trp_free (v->l);
  trp_free (v->r);
  v->r = NULL;
  v->l = free_nodes;
  free_nodes = v;

  free_nodes_cnt++;
}