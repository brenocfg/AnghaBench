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
struct TYPE_2__ {int /*<<< orphan*/  srr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSL_SE ; 
 TYPE_1__* kdb_frame ; 

void
kdb_cpu_clear_singlestep(void)
{

	kdb_frame->srr1 &= ~PSL_SE;
}