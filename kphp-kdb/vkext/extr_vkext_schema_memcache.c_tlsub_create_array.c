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
struct tl_tree_array {long args_num; void* multiplicity; TYPE_2__** args; TYPE_1__ self; } ;
struct tl_tree {int dummy; } ;
struct TYPE_4__ {void* type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  dynamic_tree_nodes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_array_methods ; 
 int /*<<< orphan*/  total_tree_nodes_existed ; 
 void* zzemalloc (int) ; 

void *tlsub_create_array (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  struct tl_tree_array *x = zzemalloc (sizeof (*x));
  dynamic_tree_nodes ++;
  total_tree_nodes_existed ++;
  x->self.ref_cnt = 1;
  x->self.flags = (long)*(IP ++);
  x->self.methods = &tl_array_methods;
  x->args_num = (long)*(IP ++);
  int i;
  x->args = zzemalloc (sizeof (void *) * x->args_num);
  for (i = x->args_num - 1; i >= 0; i--) {
    x->args[i] = zzemalloc (sizeof (*x->args[i]));
    x->args[i]->id = *(IP ++ );
    x->args[i]->type = *(--Data);
//    TL_TREE_METHODS (x->args[i]->type)->inc_ref (x->args[i]->type);
  }
  x->multiplicity = *(--Data);
#ifdef VLOG
  fprintf (stderr, "Create array\n");
#endif
//  TL_TREE_METHODS (x->multiplicity)->inc_ref (x->multiplicity);
  *(Data ++) = x;
  TLUNI_NEXT;
}