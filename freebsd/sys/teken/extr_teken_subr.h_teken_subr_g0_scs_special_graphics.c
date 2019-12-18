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
struct TYPE_3__ {int /*<<< orphan*/ * t_scs; } ;
typedef  TYPE_1__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_scs_special_graphics ; 

__attribute__((used)) static void
teken_subr_g0_scs_special_graphics(teken_t *t)
{

	t->t_scs[0] = teken_scs_special_graphics;
}