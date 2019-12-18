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
 int /*<<< orphan*/  assert (int) ; 
 int key_cmp2 (int,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 

__attribute__((used)) static struct item *tree_lookup_next (struct item *T, int key_len, const int *key, int lc, int rc) {
  if (!T) {
    return 0;
  }
  int c = key_cmp2 (key_len, key, T->key_len, T->key, min (lc, rc) - 1);
  if (c < 0) {
    assert (-c >= min (lc, rc));
    struct item *N = tree_lookup_next (T->left, key_len, key, lc, -c);
    return N ? N : T;
  } else {
    if (c == 0) { c = 2000; }
    assert (c >= min (lc, rc));
    return tree_lookup_next (T->right, key_len, key, c, rc); 
  }
}