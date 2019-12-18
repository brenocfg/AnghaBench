#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; struct TYPE_8__* uplink; struct TYPE_8__* right; struct TYPE_8__* left; } ;
typedef  TYPE_1__ utree_t ;

/* Variables and functions */
 int /*<<< orphan*/  utree_split (TYPE_1__**,TYPE_1__**,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static utree_t *utree_insert_node (utree_t *T, utree_t *P) {
  if (!T) {
    return P;
  }
  if (T->y >= P->y) {
    if (P->x < T->x) {
      T->left = utree_insert_node (T->left, P);
      if (T->left) {
        T->left->uplink = T;
      }
    } else {
      T->right = utree_insert_node (T->right, P);
      if (T->right) {
        T->right->uplink = T;
      }
    }
    return T;
  }
  utree_split (&P->left, &P->right, T, P->x);
  if (P->left) {
    P->left->uplink = P;
  }
  if (P->right) {
    P->right->uplink = P;
  }
  return P;
}