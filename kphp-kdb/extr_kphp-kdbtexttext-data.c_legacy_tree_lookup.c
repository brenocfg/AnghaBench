#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* right; struct TYPE_6__* left; } ;
typedef  TYPE_1__ ltree_t ;

/* Variables and functions */
 int /*<<< orphan*/  legacy_tree_equal (TYPE_1__*,long long,int) ; 
 scalar_t__ legacy_tree_less (long long,int,TYPE_1__*) ; 

__attribute__((used)) static ltree_t *legacy_tree_lookup (ltree_t *T, long long x, int z) {
  while (T && !legacy_tree_equal (T, x, z)) {
    T = legacy_tree_less (x, z, T) ? T->left : T->right;
  }
  return T;
}