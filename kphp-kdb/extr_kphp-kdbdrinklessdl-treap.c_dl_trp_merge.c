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
typedef  TYPE_1__* dl_trp_node_ptr ;
struct TYPE_5__ {scalar_t__ y; struct TYPE_5__* r; struct TYPE_5__* l; } ;

/* Variables and functions */

void dl_trp_merge (dl_trp_node_ptr *tr, dl_trp_node_ptr a, dl_trp_node_ptr b) {
  while (a != NULL || b != NULL) {
     if (a == NULL || (b != NULL && b->y > a->y)) {
       *tr = b;
       tr = &b->l;
       b = b->l;
     } else {
       *tr = a;
       tr = &a->r;
       a = a->r;
     }
  }
  *tr = NULL;
}