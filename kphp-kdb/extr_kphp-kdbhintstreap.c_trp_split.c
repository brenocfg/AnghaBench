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
typedef  TYPE_1__* trp_node_ptr ;
struct TYPE_5__ {int x; struct TYPE_5__* l; struct TYPE_5__* r; } ;

/* Variables and functions */

void trp_split (trp_node_ptr v, int x, trp_node_ptr *a, trp_node_ptr *b) {
  while (v != NULL) {
    if (v->x > x) {
      *a = v;
      a = &v->r;
      v = v->r;
    } else {
      *b = v;
      b = &v->l;
      v = v->l;
    }
  }
  *a = *b = NULL;
}