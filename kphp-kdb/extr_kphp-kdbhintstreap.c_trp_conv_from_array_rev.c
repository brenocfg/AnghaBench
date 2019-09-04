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
struct TYPE_4__ {int x; scalar_t__ y; struct TYPE_4__* l; struct TYPE_4__* r; } ;

/* Variables and functions */
 TYPE_1__* get_new_node () ; 
 scalar_t__ my_rand () ; 

trp_node_ptr trp_conv_from_array_rev (int *a, int n) {
  static trp_node_ptr stack[600];
//  assert (n <= 50);

  int sn = 0, i;

  stack[0] = NULL;

  for (i = n - 1; i >= 0; i--) {
    trp_node_ptr new_el = get_new_node();
    new_el->x = a[i];
    new_el->y = my_rand();
    new_el->r = NULL;
    while (sn && stack[sn - 1]->y < new_el->y) {
      sn--;
    }
    if (sn) {
      new_el->l = stack[sn - 1]->r;
      stack[sn - 1]->r = new_el;
    } else {
      new_el->l = stack[0];
    }
    stack[sn++] = new_el;
  }

  return stack[0];
}