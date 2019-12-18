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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;

/* Variables and functions */
 int acpi_PkgInt (int /*<<< orphan*/ *,int,scalar_t__*) ; 

int
acpi_PkgInt32(ACPI_OBJECT *res, int idx, uint32_t *dst)
{
    UINT64		tmp;
    int			error;

    error = acpi_PkgInt(res, idx, &tmp);
    if (error == 0)
	*dst = (uint32_t)tmp;

    return (error);
}