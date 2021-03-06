#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
struct TYPE_6__ {int z; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 TYPE_3__* GLOBAL_NODE (TYPE_1__*) ; 
 int Y_MULT_INV ; 
 int b_out_g_rev (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dtree_out_node_rev (tree_ext_small_t *T) {
  #ifdef LISTS_GT
  return b_out_g_rev (GLOBAL_NODE (T)->z, GLOBAL_NODE (T)->x);
  #else
  return b_out_g_rev (T->y * Y_MULT_INV, T->x);
  #endif
}