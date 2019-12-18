#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long long x; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ ltree_t ;

/* Variables and functions */

__attribute__((used)) static ltree_t *ltree_lookup_legacy (ltree_t *T, long long x) {
  while (T && x != T->x) {
    T = (x < T->x) ? T->left : T->right;
  }
  return T;
}