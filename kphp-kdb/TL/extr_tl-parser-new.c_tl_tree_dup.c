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
struct tl_combinator_tree {struct tl_combinator_tree* right; struct tl_combinator_tree* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct tl_combinator_tree*,struct tl_combinator_tree*,int) ; 
 struct tl_combinator_tree* zmalloc (int) ; 

struct tl_combinator_tree *tl_tree_dup (struct tl_combinator_tree *T) {
  if (!T) { return 0; }
  struct tl_combinator_tree *S = zmalloc (sizeof (*S));
  memcpy (S, T, sizeof (*S));
  S->left = tl_tree_dup (T->left);
  S->right = tl_tree_dup (T->right);
  return S;
}