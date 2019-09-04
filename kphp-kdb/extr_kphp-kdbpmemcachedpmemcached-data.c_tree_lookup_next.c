#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* right; struct TYPE_6__* left; TYPE_1__* x; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_5__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int min (int,int) ; 
 int mystrcmp2 (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree_t *tree_lookup_next (tree_t *T, const char *key, int key_len, int lc, int rc) {
  //vkprintf (1, "%s - %s [%d - %d]\n", key, T ? T->x->key : "NULL", lc, rc);
  if (!T) {
    return 0;
  }
  int c = mystrcmp2 (key, key_len, T->x->key, T->x->key_len, min (lc, rc) - 1);
  if (c < 0) {
    assert (-c >= min (lc, rc));
    tree_t *N = tree_lookup_next (T->left, key, key_len, lc, -c);
    return N ? N : T;
  } else {
    if (c == 0) { c = 2000; }
    assert (c >= min (lc, rc));
    return tree_lookup_next (T->right, key, key_len, c, rc); 
  }
}