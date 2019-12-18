#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int x1; int* extra; scalar_t__ x2; struct TYPE_4__* right; struct TYPE_4__* middle; struct TYPE_4__* left; } ;
typedef  TYPE_1__ tree23_t ;
struct TYPE_5__ {int* extra; } ;
typedef  TYPE_2__ tree23_leaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void dump_rec (tree23_t *T, int depth, int extra) {
  int i;
  if (!T) return;
  printf ("[ ");
  if (depth--) {
    dump_rec (T->left, depth, extra);
    printf ("%d", T->x1);
    for (i = -extra; i < 0; i++) {
      printf (":%d", T->extra[i]);
    }
    putchar (' ');
    if (T->x2 > T->x1) {
      dump_rec (T->middle, depth, extra);
      printf ("%d", T->x2);
      for (i = -2*extra; i < -extra; i++) {
        printf (":%d", T->extra[i]);
      }
      putchar (' ');
    }
    dump_rec (T->right, depth, extra);
  } else {
    printf ("%d", T->x1);
    for (i = -extra; i < 0; i++) {
      printf (":%d", ((tree23_leaf_t *) T)->extra[i]);
    }
    putchar (' ');
    if (T->x2 > T->x1) {
      printf ("%d", T->x2);
      for (i = -2*extra; i < -extra; i++) {
        printf (":%d", ((tree23_leaf_t *) T)->extra[i]);
      }
      putchar (' ');
    }
  }
  printf ("] ");
}