#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* right; TYPE_3__* x; struct TYPE_4__* left; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_5__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int iterator_report (TYPE_3__*) ; 
 scalar_t__ min (int,int) ; 
 int mystrcmp2 (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int tree_lookup_all_next (tree_t *T, const char *key, int key_len, int prefix_len, int strict, int lc, int rc) {
  //vkprintf (1, "%s - %s [%d - %d]\n", key, T ? T->x->key : "NULL", lc, rc);
  if (!T) {
    return 0;
  }
  int c = mystrcmp2 (key, key_len, T->x->key, T->x->key_len, min (lc, rc) - 1);
  if (c < 0 || c > prefix_len) {
    int t = tree_lookup_all_next (T->left, key, key_len, prefix_len, strict, lc, c < 0 ? -c : c);
    if (t < 0) { return t; }
  }
  if ((c == 0 && !strict) || c < -prefix_len || c > prefix_len) {
    int t = iterator_report (T->x);
    if (t < 0) { return t; }
  }
  if (c > 0 || c < -prefix_len) {
    int t = tree_lookup_all_next (T->right, key, key_len, prefix_len, strict, c < 0 ? -c : c, rc);
    if (t < 0) { return t; }
  }
  return 0;
}