#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x; struct TYPE_5__* uplink; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ utree_t ;

/* Variables and functions */

__attribute__((used)) static void utree_split (utree_t **L, utree_t **R, utree_t *T, int x) {
  if (!T) { *L = *R = 0; return; }
  if (x < T->x) {
    *R = T;
    utree_split (L, &T->left, T->left, x);
    if (T->left) {
      T->left->uplink = T;
    }
  } else {
    *L = T;
    utree_split (&T->right, R, T->right, x);
    if (T->right) {
      T->right->uplink = T;
    }
  }
}