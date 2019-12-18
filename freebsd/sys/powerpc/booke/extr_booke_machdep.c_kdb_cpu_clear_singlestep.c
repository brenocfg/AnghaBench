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
typedef  int register_t ;
struct TYPE_2__ {int /*<<< orphan*/  srr1; } ;

/* Variables and functions */
 int DBCR0_IC ; 
 int /*<<< orphan*/  PSL_DE ; 
 int /*<<< orphan*/  SPR_DBCR0 ; 
 TYPE_1__* kdb_frame ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

void
kdb_cpu_clear_singlestep(void)
{
	register_t r;

	r = mfspr(SPR_DBCR0);
	mtspr(SPR_DBCR0, r & ~DBCR0_IC);
	kdb_frame->srr1 &= ~PSL_DE;
}