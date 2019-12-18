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
struct item {struct item* right; struct item* left; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct item*) ; 
 int key_cmp (int,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct item* tree_merge (struct item*,struct item*) ; 
 int /*<<< orphan*/  update_counters (struct item*) ; 

__attribute__((used)) static struct item *tree_delete (struct item *T, int key_len, const int *key) {
  int c;
  assert (T);
  if (!(c = key_cmp (key_len, key, T->key_len, T->key))) {
    struct item *N = tree_merge (T->left, T->right);
    update_counters (N);
    return N;
  }
  if (c < 0) {
    T->left = tree_delete (T->left, key_len, key);
  } else {
    T->right = tree_delete (T->right, key_len, key);
  }
  update_counters (T);
  return T;
}