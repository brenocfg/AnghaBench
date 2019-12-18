#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* treap_node_ptr ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ pli ;
struct TYPE_5__ {struct TYPE_5__* r; int /*<<< orphan*/  val; int /*<<< orphan*/  x; struct TYPE_5__* l; } ;

/* Variables and functions */

int treap_conv_to_array (treap_node_ptr v, pli *a, int n) {
  if (v == NULL) {
    return 0;
  }
  int ln = treap_conv_to_array (v->l, a, n);
  a += ln;
  n -= ln;
  if (n) {
    a->x = v->x;
    a->y = v->val;
    a++;
    n--;
    ln++;
  }
  ln += treap_conv_to_array (v->r, a, n);
  return ln;
}