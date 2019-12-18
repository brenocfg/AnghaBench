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
 int /*<<< orphan*/  pr_debug (char*,char const*,int,unsigned long,...) ; 

__attribute__((used)) static void _dump_areas(unsigned int spe_id, unsigned long priv2,
	unsigned long problem, unsigned long ls, unsigned long shadow,
	const char* func, int line)
{
	pr_debug("%s:%d: spe_id:  %xh (%u)\n", func, line, spe_id, spe_id);
	pr_debug("%s:%d: priv2:   %lxh\n", func, line, priv2);
	pr_debug("%s:%d: problem: %lxh\n", func, line, problem);
	pr_debug("%s:%d: ls:      %lxh\n", func, line, ls);
	pr_debug("%s:%d: shadow:  %lxh\n", func, line, shadow);
}