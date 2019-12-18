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
struct ia64_sal_retval {unsigned long v0; unsigned long v1; long status; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAL_CALL (struct ia64_sal_retval,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAL_FREQ_BASE ; 

long
ia64_sal_freq_base (unsigned long which, unsigned long *ticks_per_second,
		    unsigned long *drift_info)
{
	struct ia64_sal_retval isrv;

	SAL_CALL(isrv, SAL_FREQ_BASE, which, 0, 0, 0, 0, 0, 0);
	*ticks_per_second = isrv.v0;
	*drift_info = isrv.v1;
	return isrv.status;
}