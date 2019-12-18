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
 int /*<<< orphan*/  wrperfmon (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
op_axp_cpu_stop(void *dummy)
{
	/* Disable performance monitoring for all counters.  */
	wrperfmon(0, -1);
}