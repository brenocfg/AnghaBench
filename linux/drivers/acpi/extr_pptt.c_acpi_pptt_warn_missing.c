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
 int /*<<< orphan*/  pr_warn_once (char*) ; 

__attribute__((used)) static void acpi_pptt_warn_missing(void)
{
	pr_warn_once("No PPTT table found, CPU and cache topology may be inaccurate\n");
}