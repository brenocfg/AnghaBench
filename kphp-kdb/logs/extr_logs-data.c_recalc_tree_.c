#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; int v_int; } ;
struct TYPE_7__ {int vn; struct TYPE_7__** v; TYPE_1__ tok; } ;
typedef  TYPE_2__ node ;

/* Variables and functions */
 scalar_t__ op_and ; 
 scalar_t__ op_or ; 
 int recalc_node (TYPE_2__*) ; 
 int to_bool (TYPE_2__*) ; 

inline int recalc_tree_ (node *v) {
  int i;

  int need = -1;
  if (v->tok.type == op_and) {
    need = 0;
  }
  if (v->tok.type == op_or) {
    need = 1;
  }

  if (need != -1) {
    for (i = 0; i < v->vn; i++) {
      if (!recalc_tree_ (v->v[i])) {
        return 0;
      }

      int x = to_bool (v->v[i]);
      if (x == need) {
        v->tok.v_int = need;
        return 1;
      }
    }

    v->tok.v_int = 1 - need;
    return 1;
  } else {
    for (i = 0; i < v->vn; i++) {
      if (!recalc_tree_ (v->v[i])) {
        return 0;
      }
    }

    return recalc_node (v);
  }
}