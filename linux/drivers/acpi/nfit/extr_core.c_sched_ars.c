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
struct acpi_nfit_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sched_ars (struct acpi_nfit_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sched_ars(struct acpi_nfit_desc *acpi_desc)
{
	__sched_ars(acpi_desc, 0);
}