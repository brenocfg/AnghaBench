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
struct item {struct item* left; struct item* right; scalar_t__ plus_unsure; scalar_t__ minus_unsure; scalar_t__ delta; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */
 int key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const*) ; 
 int /*<<< orphan*/  tree_count_one (struct item*,int*) ; 

__attribute__((used)) static void tree_count (struct item *T, int left_len, const int *left, int right_len, const int *right, int Z[3]) {
  struct item *L = T;
  struct item *R = T;
  while (L || R) {    
    int c1 = L ? key_cmp (L->key_len, L->key, left_len, left) : 0;
    int c2 = R ? key_cmp (R->key_len, R->key, right_len, right) : 0;
    if (L == R) {
      if (c1 <= 0) {
        if (c1 == 0) {
          tree_count_one (L, Z);
        }
        L = R = L->right;
      } else if (c2 >= 0) {
        if (c2 == 0) {
          tree_count_one (L, Z);
        }
        L = R = L->left;
      } else {
        tree_count_one (L, Z);
        L = L->left;
        R = R->right;
      }
    } else {
      if (L) {
        if (c1 >= 0) {
          if (L->right) {
            Z[0] += L->right->delta;
            Z[1] += L->right->minus_unsure;
            Z[2] += L->right->plus_unsure;
          }
          tree_count_one (L, Z);
          L = L->left;
        } else {
          L = L->right;
        }
      }
      if (R) {
        if (c2 <= 0) {
          if (R->left) {
            Z[0] += R->left->delta;
            Z[1] += R->left->minus_unsure;
            Z[2] += R->left->plus_unsure;
          }
          tree_count_one (R, Z);
          R = R->right;
        } else {
          R = R->left;
        }
      }
    }
  }
}