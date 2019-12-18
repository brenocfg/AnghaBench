#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * mr_op; } ;

/* Variables and functions */
 TYPE_1__ mem_range_softc ; 
 int /*<<< orphan*/  mr_lock ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 

void
mem_range_destroy(void)
{

	if (mem_range_softc.mr_op == NULL)
		return;
	rw_destroy(&mr_lock);
}