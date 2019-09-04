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
struct TYPE_3__ {scalar_t__ x2; scalar_t__ x1; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ld ; 
 scalar_t__ leaves ; 
 scalar_t__ lp ; 

__attribute__((used)) static void free_leaf (tree23_t *pp) {
  //printf ("delete leaf\n");
  assert (pp >= (tree23_t *)leaves && pp < (tree23_t *)(leaves + lp));
  pp->x1 = pp->x2 = 0;
  ++ld;
}