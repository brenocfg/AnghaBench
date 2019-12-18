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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_NCAPS ; 
 int /*<<< orphan*/  cpu_hwcaps ; 
 int /*<<< orphan*/  pr_emerg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_cpu_hwcaps(struct notifier_block *self, unsigned long v, void *p)
{
	/* file-wide pr_fmt adds "CPU features: " prefix */
	pr_emerg("0x%*pb\n", ARM64_NCAPS, &cpu_hwcaps);
	return 0;
}