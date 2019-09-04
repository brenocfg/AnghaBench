#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  C; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ icpl_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  ct_combinator ; 
 int /*<<< orphan*/  get_combinator_f (char const*,int,int) ; 
 TYPE_2__* zmalloc0 (int) ; 

__attribute__((used)) static icpl_cell_t *cell_new_combinator (const char *name, int length) {
  icpl_cell_t *c = zmalloc0 (sizeof (*c));
  c->type = ct_combinator;
  c->u.C = get_combinator_f (name, length, 1);
  return c;
}