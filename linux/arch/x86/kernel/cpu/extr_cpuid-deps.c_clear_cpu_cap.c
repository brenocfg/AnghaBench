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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_clear_cpu_cap (struct cpuinfo_x86*,unsigned int) ; 

void clear_cpu_cap(struct cpuinfo_x86 *c, unsigned int feature)
{
	do_clear_cpu_cap(c, feature);
}