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
struct TYPE_3__ {int x; int* extra; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ rbtree_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void dump (rbtree_t *T, int extra) {
  int i;
  if (!T) return;
  printf ("[ ");
  dump (T->left, extra);

  printf ("%d", T->x);

  for (i = 0; i < extra; i++) {
    printf (":%d", T->extra[i]);
  }

  putchar (' ');

  dump (T->right, extra);
  printf ("] ");
}