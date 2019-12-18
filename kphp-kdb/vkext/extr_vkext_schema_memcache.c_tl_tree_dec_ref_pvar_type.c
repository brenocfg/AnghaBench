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
struct TYPE_2__ {scalar_t__ ref_cnt; } ;
struct tl_tree_var_type {TYPE_1__ self; } ;
struct tl_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PFREE (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  persistent_tree_nodes ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  total_ref_cnt ; 
 int /*<<< orphan*/  zzfree (struct tl_tree_var_type*,int) ; 

void tl_tree_dec_ref_pvar_type (struct tl_tree *_x) {
  total_ref_cnt --;
  struct tl_tree_var_type *x = (void *)_x;
#ifdef VLOG
  fprintf (stderr, "Dec_ref: persistent var_type\n");
#endif
  x->self.ref_cnt --;
  if (x->self.ref_cnt > 0) { return; }
  persistent_tree_nodes --;
  zzfree (x, sizeof (*x));
  ADD_PFREE (sizeof (*x));
}