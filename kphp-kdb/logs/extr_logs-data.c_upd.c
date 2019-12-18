#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t type; int /*<<< orphan*/  param_set; int /*<<< orphan*/  param_int; } ;
typedef  TYPE_2__ token ;
struct TYPE_9__ {size_t type; int /*<<< orphan*/  param_set; int /*<<< orphan*/  param_int; } ;
struct TYPE_11__ {int vn; struct TYPE_11__** v; TYPE_1__ tok; } ;
typedef  TYPE_3__ node ;

/* Variables and functions */
 scalar_t__ IS_CONST (size_t) ; 
 scalar_t__ IS_UN (size_t) ; 
 int /*<<< orphan*/  del_node (TYPE_3__*) ; 
 TYPE_3__** dl_malloc0 (int) ; 
 TYPE_3__* new_node () ; 
 size_t op_lb ; 
 size_t op_rb ; 
 int* priority ; 
 int s1n ; 
 int s2n ; 

int upd (node **s1, token *s2, int *_s1n, int *_s2n, int p) {
#define s1n (*_s1n)
#define s2n (*_s2n)
  while (s2n && priority[s2[s2n - 1].type] <= p) {
    node *v = new_node();
    v->tok.type = s2[--s2n].type;
    v->tok.param_int = s2[s2n].param_int;
    v->tok.param_set = s2[s2n].param_set;
    if (v->tok.type == op_rb || v->tok.type == op_lb) {
      del_node (v);
      return 0;
    }
    if (IS_CONST(v->tok.type)) {
      v->vn = 0;
    } else if (IS_UN(v->tok.type)) { // unary
      v->vn = 1;
    } else {
      v->vn = 2;
    }
    v->v = dl_malloc0 (sizeof (node *) * v->vn);
    if (s1n < v->vn) {
      del_node (v);
      return 0;
    }
    s1n -= v->vn;
    int i;
    for (i = 0; i < v->vn; i++) {
      v->v[i] = s1[s1n + i];
    }
    s1[s1n++] = v;
  }
#undef s1n
#undef s2n

  return 1;
}