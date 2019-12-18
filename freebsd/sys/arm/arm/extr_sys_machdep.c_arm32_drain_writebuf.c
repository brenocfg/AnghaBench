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
struct thread {scalar_t__* td_retval; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_drain_writebuf () ; 
 int /*<<< orphan*/  cpu_l2cache_drain_writebuf () ; 
 int /*<<< orphan*/  dsb () ; 

__attribute__((used)) static int
arm32_drain_writebuf(struct thread *td, void *args)
{
	/* No args. */

#if __ARM_ARCH < 6
	cpu_drain_writebuf();
#else
	dsb();
	cpu_l2cache_drain_writebuf();
#endif
	td->td_retval[0] = 0;
	return (0);
}