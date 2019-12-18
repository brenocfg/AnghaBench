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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  gas ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int Length; scalar_t__ Pointer; } ;
struct TYPE_6__ {TYPE_3__* Elements; } ;
struct TYPE_7__ {scalar_t__ Type; TYPE_1__ Buffer; TYPE_2__ Package; } ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int EINVAL ; 
 int acpi_bus_alloc_gas (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,struct resource**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

int
acpi_PkgGas(device_t dev, ACPI_OBJECT *res, int idx, int *type, int *rid,
    struct resource **dst, u_int flags)
{
    ACPI_GENERIC_ADDRESS gas;
    ACPI_OBJECT *obj;

    obj = &res->Package.Elements[idx];
    if (obj == NULL || obj->Type != ACPI_TYPE_BUFFER ||
	obj->Buffer.Length < sizeof(ACPI_GENERIC_ADDRESS) + 3)
	return (EINVAL);

    memcpy(&gas, obj->Buffer.Pointer + 3, sizeof(gas));

    return (acpi_bus_alloc_gas(dev, type, rid, &gas, dst, flags));
}