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
typedef  int /*<<< orphan*/  tree23_leaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ld ; 
 int /*<<< orphan*/  zfree (char*,int) ; 

__attribute__((used)) static void free_leaf (tree23_t *pp, int extra) {
  //printf ("delete leaf\n");
  pp->x1 = pp->x2 = 0;
  ++ld;
  zfree ((char *) pp - 8*extra, sizeof (tree23_leaf_t) + 8*extra);
}