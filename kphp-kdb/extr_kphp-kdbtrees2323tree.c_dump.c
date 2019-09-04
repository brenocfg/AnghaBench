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
struct TYPE_3__ {int x1; int x2; struct TYPE_3__* right; struct TYPE_3__* middle; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void dump (tree23_t *T) {
  if (!T) return;
  printf ("[ ");
  if (!(T->x1 & 1)) {
    dump (T->left);
    printf ("%d ", T->x1);
    if (!(T->x2 & 1)) {
      dump (T->middle);
      printf ("%d ", T->x2);
    }
    dump (T->right);
  } else {
    printf ("%d ", T->x1);
    if (!(T->x2 & 1)) printf ("%d ", T->x2);
  }
  printf ("] ");
}