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
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ collsym_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVED ; 
 int /*<<< orphan*/  T_COLLSYM ; 
 int /*<<< orphan*/  nextpri ; 
 int /*<<< orphan*/  set_pri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_order (int /*<<< orphan*/ ) ; 

void
end_order_collsym(collsym_t *sym)
{
	start_order(T_COLLSYM);
	/* update the weight */

	set_pri(sym->ref, nextpri, RESOLVED);
	nextpri++;
}