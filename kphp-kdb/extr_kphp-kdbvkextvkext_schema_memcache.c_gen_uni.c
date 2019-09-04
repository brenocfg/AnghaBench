#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tl_tree_var_type {int var_num; } ;
struct tl_tree_var_num {int var_num; int dif; } ;
struct tl_tree_type {int children_num; struct tl_tree** children; void* type; } ;
struct tl_tree_array {int args_num; int /*<<< orphan*/ * args; struct tl_tree* multiplicity; } ;
struct tl_tree {int dummy; } ;
struct TYPE_2__ {int (* type ) (struct tl_tree*) ;} ;

/* Variables and functions */
#define  NODE_TYPE_ARRAY 132 
#define  NODE_TYPE_NAT_CONST 131 
#define  NODE_TYPE_TYPE 130 
#define  NODE_TYPE_VAR_NUM 129 
#define  NODE_TYPE_VAR_TYPE 128 
 TYPE_1__* TL_TREE_METHODS (struct tl_tree*) ; 
 int /*<<< orphan*/  assert (struct tl_tree*) ; 
 int gen_uni_arg (int /*<<< orphan*/ ,void**,int,int*) ; 
 int stub1 (struct tl_tree*) ; 
 void* tluni_check_array ; 
 void* tluni_check_nat_const ; 
 void* tluni_check_nat_var ; 
 void* tluni_check_type ; 
 void* tluni_check_type_var ; 
 void* tluni_set_nat_var ; 
 void* tluni_set_type_var ; 

int gen_uni (struct tl_tree *t, void **IP, int max_size, int *vars) {
  if (max_size <= 10) { return -1; }
  assert (t);
  int x = TL_TREE_METHODS (t)->type (t);
  int l = 0;
  int i;
  int j;
  struct tl_tree_type *t1;
  struct tl_tree_array *t2;
  int y;
  switch (x) {
  case NODE_TYPE_TYPE:
    t1 = (void *)t;
    IP[l ++] = tluni_check_type;
    IP[l ++] = ((struct tl_tree_type *)t)->type;
    for (i = 0; i < t1->children_num; i++) {
      y = gen_uni (t1->children[i], IP + l, max_size - l, vars);
      if (y < 0) { return -1; }
      l += y;
    }
    return l;
  case NODE_TYPE_NAT_CONST:
    IP[l ++] = tluni_check_nat_const;
    IP[l ++] = t;
    return l;
  case NODE_TYPE_ARRAY:
    t2 = (void *)t;
    IP[l ++] = tluni_check_array;
    IP[l ++] = t;
    y = gen_uni (t2->multiplicity, IP + l, max_size - l, vars);
    if (y < 0) { return -1; }
    l += y;
    for (i = 0; i < t2->args_num; i++) {
      y += gen_uni_arg (t2->args[i], IP + l, max_size - l, vars);
      if (y < 0) { return -1; }
      l += y;
    }
    return l;
  case NODE_TYPE_VAR_TYPE:
    i = ((struct tl_tree_var_type *)t)->var_num;
    if (!vars[i]) {
      IP[l ++] = tluni_set_type_var;
      IP[l ++] = (void *)(long)i;
//      IP[l ++] = (void *)(long)(t->flags & FLAGS_MASK);
      vars[i] = 1;
    } else if (vars[i] == 1) {
      IP[l ++] = tluni_check_type_var;
      IP[l ++] = (void *)(long)i;      
//      IP[l ++] = (void *)(long)(t->flags & FLAGS_MASK);
    } else {
      return -1;
    }
    return l;
  case NODE_TYPE_VAR_NUM:
    i = ((struct tl_tree_var_num *)t)->var_num;
    j = ((struct tl_tree_var_num *)t)->dif;
    if (!vars[i]) {
      IP[l ++] = tluni_set_nat_var;
      IP[l ++] = (void *)(long)i;
      IP[l ++] = (void *)(long)j;
      vars[i] = 2;
    } else if (vars[i] == 2) {
      IP[l ++] = tluni_check_nat_var;
      IP[l ++] = (void *)(long)i;
      IP[l ++] = (void *)(long)j;
    } else {
      return -1;
    }
    return l;
  default:
    assert (0);
    return -1;
  }
}