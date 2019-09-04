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
struct item {scalar_t__ y; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; struct item* right; struct item* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_split (struct item**,struct item**,struct item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_counters (struct item*) ; 

__attribute__((used)) static struct item *tree_insert (struct item *T, struct item *N) {
  if (!T) { 
    update_counters (N);
    return N;
  }
  int c;
  assert (c = key_cmp (N->key_len, N->key, T->key_len, T->key));
  if (T->y >= N->y) {
    if (c < 0) {
      T->left = tree_insert (T->left, N);
    } else {
      T->right = tree_insert (T->right, N);
    }
    update_counters (T);
    return T;
  }
  tree_split (&N->left, &N->right, T, N->key_len, N->key);
  update_counters (N);
  return N;
}