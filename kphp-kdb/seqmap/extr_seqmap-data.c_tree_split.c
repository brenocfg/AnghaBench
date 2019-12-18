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
 scalar_t__ key_cmp (int,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_counters (struct item*) ; 

__attribute__((used)) static void tree_split (struct item **L, struct item **R, struct item *T, int key_len, const int *key) {
  if (!T) { *L = *R = 0; return; }
  if (key_cmp (key_len, key, T->key_len, T->key) < 0) {
    *R = T;
    tree_split (L, &T->left, T->left, key_len, key);
  } else {
    *L = T;
    tree_split (&T->right, R, T->right, key_len, key);
  }
  update_counters (T);
}