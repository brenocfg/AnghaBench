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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int ref_cnt; long flags; int /*<<< orphan*/ * methods; } ;
struct tl_tree_type {int children_num; void** children; TYPE_2__* type; TYPE_1__ self; } ;
struct tl_tree {int dummy; } ;
struct TYPE_4__ {char* id; int arity; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  dynamic_tree_nodes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_type_methods ; 
 int /*<<< orphan*/  total_ref_cnt ; 
 int /*<<< orphan*/  total_tree_nodes_existed ; 
 void* zzemalloc (int) ; 

void *tlsub_create_type (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  struct tl_tree_type *x = zzemalloc (sizeof (*x));
  dynamic_tree_nodes ++;
  total_tree_nodes_existed ++;
  x->self.ref_cnt = 1;
  total_ref_cnt ++;
  x->self.flags = (long)*(IP ++);
  x->self.methods = &tl_type_methods;
  x->type = *(IP ++);
#ifdef VLOG
  fprintf (stderr, "Create type %s. flags = %d\n", x->type->id, x->self.flags);
#endif
  x->children_num = x->type->arity;
  x->children = zzemalloc (sizeof (void *) * x->children_num);
  int i;
  for (i = x->children_num - 1; i >= 0; i--) {
    x->children[i] = *(--Data);
//    TL_TREE_METHODS (x->children[i])->inc_ref (x->children[i]);
  }
  *(Data ++) = x;
//  fprintf (stderr, "create type %s\n", x->type->id);
  TLUNI_NEXT;
}