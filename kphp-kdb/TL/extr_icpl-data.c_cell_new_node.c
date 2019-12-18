#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* right; TYPE_3__* left; } ;
struct TYPE_9__ {TYPE_1__ p; } ;
struct TYPE_10__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ icpl_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  ct_node ; 
 TYPE_3__* zmalloc0 (int) ; 

__attribute__((used)) static icpl_cell_t *cell_new_node (icpl_cell_t *left, icpl_cell_t *right) {
  if (left == NULL) {
    return right;
  }
  icpl_cell_t *c = zmalloc0 (sizeof (*c));
  c->type = ct_node;
  c->u.p.left = left;
  c->u.p.right = right;
  return c;
}