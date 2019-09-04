#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* right; struct TYPE_3__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  writeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writeout_char (int) ; 

__attribute__((used)) static void dump_tree (tree_t *T) {
  if (T) {
    writeout_char (1);
  } else {
    writeout_char (0);
    return;
  }
  writeout (&T->x, 16);
  dump_tree (T->left);
  dump_tree (T->right);
}