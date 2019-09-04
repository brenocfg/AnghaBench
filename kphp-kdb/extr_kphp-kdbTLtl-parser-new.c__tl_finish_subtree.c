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
struct tl_type {int dummy; } ;
struct tl_combinator_tree {scalar_t__ type; int type_len; scalar_t__ act; long long type_flags; TYPE_1__* right; struct tl_combinator_tree* left; struct tl_type* data; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ type_len; } ;

/* Variables and functions */
 scalar_t__ act_arg ; 
 scalar_t__ act_type ; 
 int /*<<< orphan*/  assert (int) ; 
 int tl_type_set_params (struct tl_type*,int,long long) ; 
 scalar_t__ type_num ; 
 scalar_t__ type_num_value ; 
 scalar_t__ type_type ; 

int _tl_finish_subtree (struct tl_combinator_tree *R, int x, long long y) {
  assert (R->type == type_type);
  assert (R->type_len < 0);
  assert (R->act == act_arg || R->act == act_type);
  R->type_len = x;
  R->type_flags = y;
  if (R->act == act_type) {
    struct tl_type *t = R->data;
    assert (t);
    return tl_type_set_params (t, x, y);
  }
  assert ((R->right->type == type_type && R->right->type_len == 0) || R->right->type == type_num || R->right->type == type_num_value);
  return _tl_finish_subtree (R->left, x + 1, y * 2 + (R->right->type == type_num || R->right->type == type_num_value));
}