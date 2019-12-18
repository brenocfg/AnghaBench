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
struct TYPE_4__ {int ref_cnt; } ;
struct tl_tree_type {int children_num; struct tl_tree_type* children; TYPE_2__ self; TYPE_1__* type; } ;
struct tl_tree {int dummy; } ;
struct TYPE_3__ {char* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PFREE (int) ; 
 int /*<<< orphan*/  DEC_REF (struct tl_tree_type) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  persistent_tree_nodes ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  total_ref_cnt ; 
 int /*<<< orphan*/  zzfree (struct tl_tree_type*,int) ; 

void tl_tree_dec_ref_ptype (struct tl_tree *_x) {
  total_ref_cnt --;
  struct tl_tree_type *x = (void *)_x;
#ifdef VLOG
  fprintf (stderr, "Dec_ref: persistent type %s. Self ref_cnt = %d, children_num = %d\n", x->type->id, x->self.ref_cnt, x->children_num);
#endif
  x->self.ref_cnt --;
  if (x->self.ref_cnt > 0) { return; }
  persistent_tree_nodes --;
  int i;
  for (i = 0; i < x->children_num; i++) {
    DEC_REF (x->children[i]);
  }
  zzfree (x->children, sizeof (void *) * x->children_num);
  ADD_PFREE (sizeof (void *) * x->children_num);
  zzfree (x, sizeof (*x));
  ADD_PFREE (sizeof (*x));
}