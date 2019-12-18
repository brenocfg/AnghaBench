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
struct pmc_mdep {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
uncore_pcpu_noop(struct pmc_mdep *md, int cpu)
{
	(void) md;
	(void) cpu;
	return (0);
}