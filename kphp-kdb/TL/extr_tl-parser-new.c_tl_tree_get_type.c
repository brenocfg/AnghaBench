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
struct tl_type {int dummy; } ;
struct tl_combinator_tree {scalar_t__ type; scalar_t__ act; struct tl_type* data; struct tl_combinator_tree* left; } ;

/* Variables and functions */
 scalar_t__ act_array ; 
 scalar_t__ act_type ; 
 scalar_t__ act_var ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ type_type ; 

struct tl_type *tl_tree_get_type (struct tl_combinator_tree *T) {
  assert (T->type == type_type);
  if (T->act == act_array) { return 0;}
  while (T->left) {
    T = T->left;
    if (T->act == act_array) { return 0;}
    assert (T->type == type_type);
  }
  assert (T->act == act_type || T->act == act_var || T->act == act_array);
  return T->act == act_type ? T->data : 0;
}