#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  gas ;
struct TYPE_10__ {scalar_t__ SpaceId; int BitWidth; int BitOffset; int AccessWidth; int /*<<< orphan*/  Address; } ;
struct TYPE_8__ {int Length; scalar_t__ Pointer; } ;
struct TYPE_7__ {TYPE_3__* Elements; } ;
struct TYPE_9__ {scalar_t__ Type; TYPE_2__ Buffer; TYPE_1__ Package; } ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  TYPE_4__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_FIXED_HARDWARE ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int EINVAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,scalar_t__,int) ; 

int
acpi_PkgFFH_IntelCpu(ACPI_OBJECT *res, int idx, int *vendor, int *class,
    uint64_t *address, int *accsize)
{
    ACPI_GENERIC_ADDRESS gas;
    ACPI_OBJECT *obj;

    obj = &res->Package.Elements[idx];
    if (obj == NULL || obj->Type != ACPI_TYPE_BUFFER ||
	obj->Buffer.Length < sizeof(ACPI_GENERIC_ADDRESS) + 3)
	return (EINVAL);

    memcpy(&gas, obj->Buffer.Pointer + 3, sizeof(gas));
    if (gas.SpaceId != ACPI_ADR_SPACE_FIXED_HARDWARE)
	return (ERESTART);
    *vendor = gas.BitWidth;
    *class = gas.BitOffset;
    *address = gas.Address;
    *accsize = gas.AccessWidth;
    return (0);
}