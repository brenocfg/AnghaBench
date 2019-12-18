#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct find_iter_args {scalar_t__ i; int /*<<< orphan*/ * res; } ;
struct TYPE_3__ {scalar_t__ Type; } ;
typedef  TYPE_1__ ACPI_DMAR_HEADER ;
typedef  int /*<<< orphan*/  ACPI_DMAR_HARDWARE_UNIT ;

/* Variables and functions */
 scalar_t__ ACPI_DMAR_TYPE_HARDWARE_UNIT ; 

__attribute__((used)) static int
dmar_find_iter(ACPI_DMAR_HEADER *dmarh, void *arg)
{
	struct find_iter_args *fia;

	if (dmarh->Type != ACPI_DMAR_TYPE_HARDWARE_UNIT)
		return (1);

	fia = arg;
	if (fia->i == 0) {
		fia->res = (ACPI_DMAR_HARDWARE_UNIT *)dmarh;
		return (0);
	}
	fia->i--;
	return (1);
}