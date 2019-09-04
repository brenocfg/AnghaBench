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
struct tree {int text; int extra; struct tree* right; struct tree* left; } ;

/* Variables and functions */

unsigned count (struct tree *tree, int text) {
  if (!tree) {
    return 0;
  }
  if (tree->text == text) {
    return tree->extra;
  }
  if (tree->text != 0) {
    return 0;
  }
  return count (tree->left, text) + count (tree->right, text);
}