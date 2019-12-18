#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  __cl_timer_prov_destroy () ; 
 int /*<<< orphan*/  cl_atomic_spinlock ; 
 int /*<<< orphan*/  cl_spinlock_destroy (int /*<<< orphan*/ *) ; 

void complib_exit(void)
{
	__cl_timer_prov_destroy();
	cl_spinlock_destroy(&cl_atomic_spinlock);
}