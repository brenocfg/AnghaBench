#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tl_tree_nat_const {int dummy; } ;
struct tl_tree {scalar_t__ ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_FREE (int) ; 
 int /*<<< orphan*/  persistent_tree_nodes ; 
 int /*<<< orphan*/  total_ref_cnt ; 
 int /*<<< orphan*/  zzfree (struct tl_tree*,int) ; 

void tl_tree_dec_ref_pnat_const_full (struct tl_tree *_x) {
  _x->ref_cnt --;
  total_ref_cnt --;
  if (_x->ref_cnt > 0) { return; }
  persistent_tree_nodes --;
  zzfree (_x, sizeof (struct tl_tree_nat_const));
  ADD_FREE (sizeof (struct tl_tree_nat_const));
  return;
}