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
 scalar_t__ CPU_IMPL_SPARC64V ; 
 scalar_t__ CPU_IMPL_ULTRASPARCIII ; 
 int /*<<< orphan*/  tick ; 
 int /*<<< orphan*/  wrpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrstick (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tick_clear(u_int cpu_impl)
{

	if (cpu_impl == CPU_IMPL_SPARC64V ||
	    cpu_impl >= CPU_IMPL_ULTRASPARCIII)
		wrstick(0, 0);
	wrpr(tick, 0, 0);
}