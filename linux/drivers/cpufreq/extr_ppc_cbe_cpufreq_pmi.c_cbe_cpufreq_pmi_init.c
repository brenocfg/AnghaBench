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
 int cbe_cpufreq_has_pmi ; 
 int /*<<< orphan*/  cbe_pmi_handler ; 
 int /*<<< orphan*/  pmi_register_handler (int /*<<< orphan*/ *) ; 

void cbe_cpufreq_pmi_init(void)
{
	if (!pmi_register_handler(&cbe_pmi_handler))
		cbe_cpufreq_has_pmi = true;
}