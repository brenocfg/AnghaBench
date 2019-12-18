#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_6__ {int /*<<< orphan*/  Value; } ;
struct TYPE_5__ {TYPE_3__* Elements; } ;
struct TYPE_7__ {scalar_t__ Type; TYPE_2__ Integer; TYPE_1__ Package; } ;
typedef  TYPE_3__ ACPI_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EINVAL ; 

int
acpi_PkgInt(ACPI_OBJECT *res, int idx, UINT64 *dst)
{
    ACPI_OBJECT		*obj;

    obj = &res->Package.Elements[idx];
    if (obj->Type != ACPI_TYPE_INTEGER)
	return (EINVAL);
    *dst = obj->Integer.Value;

    return (0);
}