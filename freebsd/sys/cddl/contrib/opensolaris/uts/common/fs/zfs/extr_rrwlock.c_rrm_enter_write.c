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
struct TYPE_3__ {int /*<<< orphan*/ * locks; } ;
typedef  TYPE_1__ rrmlock_t ;

/* Variables and functions */
 int RRM_NUM_LOCKS ; 
 int /*<<< orphan*/  rrw_enter_write (int /*<<< orphan*/ *) ; 

void
rrm_enter_write(rrmlock_t *rrl)
{
	int i;

	for (i = 0; i < RRM_NUM_LOCKS; i++)
		rrw_enter_write(&rrl->locks[i]);
}