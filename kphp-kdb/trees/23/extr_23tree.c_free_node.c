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
struct TYPE_3__ {scalar_t__ x2; scalar_t__ x1; scalar_t__ right; scalar_t__ middle; scalar_t__ left; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nd ; 
 scalar_t__ nodes ; 
 scalar_t__ np ; 

__attribute__((used)) static void free_node (tree23_t *pp) {
  //printf ("delete node\n");
  assert (pp >= (tree23_t *)nodes && pp < (tree23_t *)(nodes + np));
  pp->left = pp->middle = pp->right = 0;
  pp->x1 = pp->x2 = 0;
  ++nd;
}