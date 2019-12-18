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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  OF_release (void*,scalar_t__) ; 
 int /*<<< orphan*/  openfirmware ; 

void
OF_chain(void *virt, u_int size, void (*entry)(), void *arg, u_int len)
{
	/*
	 * This is a REALLY dirty hack till the firmware gets this going
	 */
#if 0
	if (size > 0)
		OF_release(virt, size);
#endif
	entry(0, 0, openfirmware, arg, len);
}