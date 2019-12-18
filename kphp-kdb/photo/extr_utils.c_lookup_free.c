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
struct TYPE_3__ {int n; scalar_t__ real_n; int /*<<< orphan*/ * y; int /*<<< orphan*/ * x; int /*<<< orphan*/  new_v; } ;
typedef  TYPE_1__ lookup ;

/* Variables and functions */
 int /*<<< orphan*/  map_int_int_free (int /*<<< orphan*/ *) ; 

void lookup_free (lookup *l) {
  map_int_int_free (&l->new_v);
  l->x = NULL;
  l->y = NULL;
  l->n = -2;

#ifdef LOOKUP_CNT
  l->real_n = 0;
#endif
}