#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ref_cnt; int flags; int /*<<< orphan*/ * methods; } ;
struct tl_tree_array {int args_num; TYPE_1__ self; TYPE_2__** args; int /*<<< orphan*/  multiplicity; } ;
typedef  void tl_tree ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PMALLOC (int) ; 
 int FLAG_NOVAR ; 
 int /*<<< orphan*/  persistent_tree_nodes ; 
 scalar_t__ read_args_list (TYPE_2__**,int,int*) ; 
 int /*<<< orphan*/  read_nat_expr (int*) ; 
 int /*<<< orphan*/  read_tree (int*) ; 
 int schema_version ; 
 int /*<<< orphan*/  tl_parray_methods ; 
 scalar_t__ tl_parse_error () ; 
 int tl_parse_int () ; 
 int /*<<< orphan*/  total_ref_cnt ; 
 int /*<<< orphan*/  total_tree_nodes_existed ; 
 void* zzmalloc0 (int) ; 

struct tl_tree *read_array (int *var_num) {
  struct tl_tree_array *T = zzmalloc0 (sizeof (*T));
  ADD_PMALLOC (sizeof (*T));
  T->self.ref_cnt = 1;
  total_ref_cnt ++;
  persistent_tree_nodes ++;
  total_tree_nodes_existed ++;
  T->self.methods = &tl_parray_methods;
  T->self.flags = 0;
  if (schema_version >= 2) {
    T->multiplicity = read_nat_expr (var_num);
  } else {
    T->multiplicity = read_tree (var_num);
  }
  if (!T->multiplicity) {
    return 0;
  }
  T->args_num = tl_parse_int ();
  if (T->args_num <= 0 || T->args_num > 1000 || tl_parse_error ()) {
    return 0;
  }
  T->args = zzmalloc0 (sizeof (void *) * T->args_num);
  ADD_PMALLOC (sizeof (void *) * T->args_num);
  if (read_args_list (T->args, T->args_num, var_num) < 0) {
    return 0;
  }
  T->self.flags |= FLAG_NOVAR;
  int i;
  for (i = 0; i < T->args_num; i++) {
    if (!(T->args[i]->flags & FLAG_NOVAR)) {
      T->self.flags &= ~FLAG_NOVAR;
    }
  }
  return (void *)T;
}