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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ icpl_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  ct_any ; 
 TYPE_1__* zmalloc0 (int) ; 

__attribute__((used)) static icpl_cell_t *cell_new_any (void) {
  icpl_cell_t *c = zmalloc0 (sizeof (*c));
  c->type = ct_any;
  return c;
}