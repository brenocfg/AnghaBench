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
struct TYPE_2__ {int td_pflags; } ;

/* Variables and functions */
 int TDP_NOFAULTING ; 
 TYPE_1__* curthread ; 

int
linux_in_atomic(void)
{

	return ((curthread->td_pflags & TDP_NOFAULTING) != 0);
}