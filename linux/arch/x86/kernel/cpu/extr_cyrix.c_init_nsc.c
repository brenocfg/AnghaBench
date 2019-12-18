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
struct cpuinfo_x86 {int x86; int x86_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_detect_cache_sizes (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_cyrix (struct cpuinfo_x86*) ; 

__attribute__((used)) static void init_nsc(struct cpuinfo_x86 *c)
{
	/*
	 * There may be GX1 processors in the wild that are branded
	 * NSC and not Cyrix.
	 *
	 * This function only handles the GX processor, and kicks every
	 * thing else to the Cyrix init function above - that should
	 * cover any processors that might have been branded differently
	 * after NSC acquired Cyrix.
	 *
	 * If this breaks your GX1 horribly, please e-mail
	 * info-linux@ldcmail.amd.com to tell us.
	 */

	/* Handle the GX (Formally known as the GX2) */

	if (c->x86 == 5 && c->x86_model == 5)
		cpu_detect_cache_sizes(c);
	else
		init_cyrix(c);
}