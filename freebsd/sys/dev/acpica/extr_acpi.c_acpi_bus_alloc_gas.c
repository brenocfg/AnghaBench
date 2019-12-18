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
typedef  int u_int ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int SpaceId; int BitWidth; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
#define  ACPI_ADR_SPACE_SYSTEM_IO 129 
#define  ACPI_ADR_SPACE_SYSTEM_MEMORY 128 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int RF_ACTIVE ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

int
acpi_bus_alloc_gas(device_t dev, int *type, int *rid, ACPI_GENERIC_ADDRESS *gas,
    struct resource **res, u_int flags)
{
    int error, res_type;

    error = ENOMEM;
    if (type == NULL || rid == NULL || gas == NULL || res == NULL)
	return (EINVAL);

    /* We only support memory and IO spaces. */
    switch (gas->SpaceId) {
    case ACPI_ADR_SPACE_SYSTEM_MEMORY:
	res_type = SYS_RES_MEMORY;
	break;
    case ACPI_ADR_SPACE_SYSTEM_IO:
	res_type = SYS_RES_IOPORT;
	break;
    default:
	return (EOPNOTSUPP);
    }

    /*
     * If the register width is less than 8, assume the BIOS author means
     * it is a bit field and just allocate a byte.
     */
    if (gas->BitWidth && gas->BitWidth < 8)
	gas->BitWidth = 8;

    /* Validate the address after we're sure we support the space. */
    if (gas->Address == 0 || gas->BitWidth == 0)
	return (EINVAL);

    bus_set_resource(dev, res_type, *rid, gas->Address,
	gas->BitWidth / 8);
    *res = bus_alloc_resource_any(dev, res_type, rid, RF_ACTIVE | flags);
    if (*res != NULL) {
	*type = res_type;
	error = 0;
    } else
	bus_delete_resource(dev, res_type, *rid);

    return (error);
}