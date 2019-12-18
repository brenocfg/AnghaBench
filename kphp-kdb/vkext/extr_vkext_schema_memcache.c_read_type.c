#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ref_cnt; int flags; int /*<<< orphan*/ * methods; } ;
struct tl_tree_type {int children_num; TYPE_1__ self; TYPE_3__** children; TYPE_2__* type; } ;
typedef  void tl_tree ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {int arity; int params_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PMALLOC (int) ; 
 int FLAG_NOVAR ; 
 int TLS_EXPR_NAT ; 
 int TLS_EXPR_TYPE ; 
 int /*<<< orphan*/  TL_IS_NAT_VAR (TYPE_3__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  persistent_tree_nodes ; 
 TYPE_3__* read_nat_expr (int*) ; 
 TYPE_3__* read_tree (int*) ; 
 TYPE_3__* read_type_expr (int*) ; 
 int schema_version ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tl_parse_error () ; 
 void* tl_parse_int () ; 
 int /*<<< orphan*/  tl_ptype_methods ; 
 TYPE_2__* tl_type_get_by_name (void*) ; 
 int /*<<< orphan*/  total_ref_cnt ; 
 int /*<<< orphan*/  total_tree_nodes_existed ; 
 int verbosity ; 
 void* zzmalloc0 (int) ; 

struct tl_tree *read_type (int *var_num) {
  struct tl_tree_type *T = zzmalloc0 (sizeof (*T));
  ADD_PMALLOC (sizeof (*T));
  T->self.ref_cnt = 1;
  total_ref_cnt ++;
  persistent_tree_nodes ++;
  total_tree_nodes_existed ++;
  T->self.methods = &tl_ptype_methods;
 
  T->type = tl_type_get_by_name (tl_parse_int ());
  if (!T->type) {
    return 0;
  }
  T->self.flags = tl_parse_int ();
  T->children_num = tl_parse_int ();
  if (verbosity >= 2) {
    fprintf (stderr, "T->flags = %d, T->chilren_num = %d\n", T->self.flags, T->children_num);
  }
  if (tl_parse_error () || T->type->arity != T->children_num) {
    return 0;
  }
  if (T->children_num < 0 || T->children_num > 1000) {
    return 0;
  }
  T->children = zzmalloc0 (sizeof (void *) * T->children_num);
  ADD_PMALLOC (sizeof (void *) * T->children_num);
  int i;
  T->self.flags |= FLAG_NOVAR;
  for (i = 0; i < T->children_num; i++) {
    if (schema_version >= 2) {
      int t = tl_parse_int ();
      if (tl_parse_error ()) {
        return 0;
      }
      if (t == TLS_EXPR_NAT) {
        if (!(T->type->params_types & (1 << i))) {
          return 0;
        }
        T->children[i] = read_nat_expr (var_num);
      } else if (t == TLS_EXPR_TYPE) {
        if ((T->type->params_types & (1 << i))) {
          return 0;
        }
        T->children[i] = read_type_expr (var_num);
      } else {
        return 0;
      }
    } else {
      T->children[i] = read_tree (var_num);
    }
    if (!T->children[i]) {
      return 0;
    }
    if (!TL_IS_NAT_VAR (T->children[i]) && !(T->children[i]->flags & FLAG_NOVAR)) {
      T->self.flags &= ~FLAG_NOVAR;
    }
  }
  return (void *)T;
}