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
struct tl_tree {int dummy; } ;

/* Variables and functions */
 scalar_t__ var_nat_const_to_int (struct tl_tree*) ; 

int tl_tree_eq_nat_const (struct tl_tree *x, struct tl_tree *y) {
  //return (x == y);
  return var_nat_const_to_int (x) == var_nat_const_to_int (y);
}