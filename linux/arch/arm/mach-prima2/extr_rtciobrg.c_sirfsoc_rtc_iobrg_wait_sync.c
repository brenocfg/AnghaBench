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
 scalar_t__ SIRFSOC_CPUIOBRG_CTRL ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ sirfsoc_rtciobrg_base ; 

void sirfsoc_rtc_iobrg_wait_sync(void)
{
	while (readl_relaxed(sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_CTRL))
		cpu_relax();
}