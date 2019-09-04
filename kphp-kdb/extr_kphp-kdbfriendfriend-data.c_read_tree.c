#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* right; struct TYPE_4__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* new_tree_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readadv (int) ; 
 char* readin (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static tree_t *read_tree (void) {
  char *ptr = readin (1);
  if (!ptr) {
    fprintf (stderr, "Unexpected end of file in read_tree\n");
    return 0;
  }
  char c = ptr[0];
  readadv (1);
  assert (c == 0 || c == 1);
  if (!c) {
    return 0;
  }
  ptr = readin (16);
  if (!ptr) {
    fprintf (stderr, "Unexpected end of file in read_tree\n");
    return 0;
  }
  tree_t *T = new_tree_node (0, 0);
  memcpy (&T->x, ptr, 16);
  readadv (16);
  T->left = read_tree ();
  T->right = read_tree ();
  return T;
}