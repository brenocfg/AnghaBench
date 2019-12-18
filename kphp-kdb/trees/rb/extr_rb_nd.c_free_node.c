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
struct TYPE_3__ {scalar_t__ x; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ rbtree_t ;

/* Variables and functions */
 int /*<<< orphan*/  nd ; 
 int /*<<< orphan*/  zfree (char*,int) ; 

__attribute__((used)) static void free_node (rbtree_t *N, int extra) {
  //printf ("delete node\n");
  N->left = N->right = 0;
  N->x = 0;
  ++nd;
  zfree ((char *) N, sizeof (rbtree_t) + 4*extra);
}