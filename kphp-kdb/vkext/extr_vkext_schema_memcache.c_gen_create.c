#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tl_tree_var_type {scalar_t__ var_num; } ;
struct tl_tree_var_num {scalar_t__ dif; scalar_t__ var_num; } ;
struct TYPE_4__ {int flags; } ;
struct tl_tree_type {int children_num; void* type; TYPE_1__ self; struct tl_tree** children; } ;
struct TYPE_5__ {int flags; } ;
struct tl_tree_array {int args_num; struct tl_tree** args; TYPE_2__ self; struct tl_tree* multiplicity; } ;
struct tl_tree {int flags; void* id; struct tl_tree* type; } ;
struct TYPE_6__ {int (* type ) (struct tl_tree*) ;} ;

/* Variables and functions */
 int FLAGS_MASK ; 
 int FLAG_NOVAR ; 
#define  NODE_TYPE_ARRAY 132 
#define  NODE_TYPE_NAT_CONST 131 
#define  NODE_TYPE_TYPE 130 
#define  NODE_TYPE_VAR_NUM 129 
#define  NODE_TYPE_VAR_TYPE 128 
 int /*<<< orphan*/  TL_IS_NAT_VAR (struct tl_tree*) ; 
 TYPE_3__* TL_TREE_METHODS (struct tl_tree*) ; 
 int /*<<< orphan*/  assert (struct tl_tree*) ; 
 int stub1 (struct tl_tree*) ; 
 void* tls_push ; 
 void* tlsub_create_array ; 
 void* tlsub_create_type ; 
 void* tlsub_push_nat_var ; 
 void* tlsub_push_type_var ; 

int gen_create (struct tl_tree *t, void **IP, int max_size, int *vars) {
  if (max_size <= 10) { return -1; }
  int x = TL_TREE_METHODS (t)->type (t);
  int l = 0;
  if (!TL_IS_NAT_VAR (t) && (t->flags & FLAG_NOVAR)) {
    IP[l ++] = tls_push;
//    TL_TREE_METHODS (t)->inc_ref (t);
    IP[l ++] = t;
    return l;
  }
  int i;
  int y;
  struct tl_tree_type *t1;
  struct tl_tree_array *t2;
  switch (x) {
  case NODE_TYPE_TYPE:
    t1 = (void *)t;
    for (i = 0; i < t1->children_num; i++) {
      y = gen_create (t1->children[i], IP + l, max_size - l, vars);
      if (y < 0) { return -1; }
      l += y;
    }
    if (l + 10 >= max_size) { return -1; }
    IP[l ++] = tlsub_create_type;
    IP[l ++] = (void *)(long)(t1->self.flags & FLAGS_MASK);
    IP[l ++] = t1->type;
    return l;
  case NODE_TYPE_NAT_CONST:
    IP[l ++] = tls_push;
    IP[l ++] = t;
    return l;
  case NODE_TYPE_ARRAY:
    t2 = (void *)t;
    assert (t2->multiplicity);
    y = gen_create (t2->multiplicity, IP + l, max_size - l, vars);
    if (y < 0) { return -1; }
    l += y;

    for (i = 0; i < t2->args_num; i++) {
      assert (t2->args[i]);
      //y = gen_field (t2->args[i], IP + l, max_size - l, vars, i);
      y = gen_create (t2->args[i]->type, IP + l, max_size - l, vars);
      if (y < 0) { return -1; }
      l += y;
    }
    if (l + 10 + t2->args_num >= max_size) { return -1; }

    IP[l ++] = tlsub_create_array;
    IP[l ++] = (void *)(long)(t2->self.flags & FLAGS_MASK);
    IP[l ++] = (void *)(long)t2->args_num;
    for (i = t2->args_num - 1; i >= 0; i--) {
      IP[l ++] = t2->args[i]->id;
    }
    return l;
  case NODE_TYPE_VAR_TYPE:
    IP[l ++] = tlsub_push_type_var;
    IP[l ++] = (void *)(long)((struct tl_tree_var_type *)t)->var_num;
    //IP[l ++] = (void *)(long)(t->flags & FLAGS_MASK);
    return l;
  case NODE_TYPE_VAR_NUM:
    IP[l ++] = tlsub_push_nat_var;
    IP[l ++] = (void *)(long)((struct tl_tree_var_num *)t)->var_num;
    IP[l ++] = (void *)(long)((struct tl_tree_var_num *)t)->dif;
    return l;
  default:
    assert (0);
    return -1;
  }
}