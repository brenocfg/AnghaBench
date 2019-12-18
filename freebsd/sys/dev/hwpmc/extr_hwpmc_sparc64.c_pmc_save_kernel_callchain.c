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
struct trapframe {int dummy; } ;

/* Variables and functions */

int
pmc_save_kernel_callchain(uintptr_t *cc, int maxsamples,
    struct trapframe *tf)
{
	(void) cc;
	(void) maxsamples;
	(void) tf;
	return (0);
}