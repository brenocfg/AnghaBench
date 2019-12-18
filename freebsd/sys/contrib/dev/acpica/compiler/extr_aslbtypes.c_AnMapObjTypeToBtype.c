#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int ParseOpcode; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BTYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_BTYPE_BUFFER_FIELD ; 
 int /*<<< orphan*/  ACPI_BTYPE_DDB_HANDLE ; 
 int /*<<< orphan*/  ACPI_BTYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_BTYPE_EVENT ; 
 int /*<<< orphan*/  ACPI_BTYPE_FIELD_UNIT ; 
 int /*<<< orphan*/  ACPI_BTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_BTYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_BTYPE_MUTEX ; 
 int /*<<< orphan*/  ACPI_BTYPE_OBJECTS_AND_REFS ; 
 int /*<<< orphan*/  ACPI_BTYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_BTYPE_POWER ; 
 int /*<<< orphan*/  ACPI_BTYPE_REGION ; 
 int /*<<< orphan*/  ACPI_BTYPE_STRING ; 
 int /*<<< orphan*/  ACPI_BTYPE_THERMAL ; 
#define  PARSEOP_OBJECTTYPE_BFF 142 
#define  PARSEOP_OBJECTTYPE_BUF 141 
#define  PARSEOP_OBJECTTYPE_DDB 140 
#define  PARSEOP_OBJECTTYPE_DEV 139 
#define  PARSEOP_OBJECTTYPE_EVT 138 
#define  PARSEOP_OBJECTTYPE_FLD 137 
#define  PARSEOP_OBJECTTYPE_INT 136 
#define  PARSEOP_OBJECTTYPE_MTH 135 
#define  PARSEOP_OBJECTTYPE_MTX 134 
#define  PARSEOP_OBJECTTYPE_OPR 133 
#define  PARSEOP_OBJECTTYPE_PKG 132 
#define  PARSEOP_OBJECTTYPE_POW 131 
#define  PARSEOP_OBJECTTYPE_STR 130 
#define  PARSEOP_OBJECTTYPE_THZ 129 
#define  PARSEOP_OBJECTTYPE_UNK 128 

UINT32
AnMapObjTypeToBtype (
    ACPI_PARSE_OBJECT       *Op)
{

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_OBJECTTYPE_BFF:        /* "BuffFieldObj" */

        return (ACPI_BTYPE_BUFFER_FIELD);

    case PARSEOP_OBJECTTYPE_BUF:        /* "BuffObj" */

        return (ACPI_BTYPE_BUFFER);

    case PARSEOP_OBJECTTYPE_DDB:        /* "DDBHandleObj" */

        return (ACPI_BTYPE_DDB_HANDLE);

    case PARSEOP_OBJECTTYPE_DEV:        /* "DeviceObj" */

        return (ACPI_BTYPE_DEVICE);

    case PARSEOP_OBJECTTYPE_EVT:        /* "EventObj" */

        return (ACPI_BTYPE_EVENT);

    case PARSEOP_OBJECTTYPE_FLD:        /* "FieldUnitObj" */

        return (ACPI_BTYPE_FIELD_UNIT);

    case PARSEOP_OBJECTTYPE_INT:        /* "IntObj" */

        return (ACPI_BTYPE_INTEGER);

    case PARSEOP_OBJECTTYPE_MTH:        /* "MethodObj" */

        return (ACPI_BTYPE_METHOD);

    case PARSEOP_OBJECTTYPE_MTX:        /* "MutexObj" */

        return (ACPI_BTYPE_MUTEX);

    case PARSEOP_OBJECTTYPE_OPR:        /* "OpRegionObj" */

        return (ACPI_BTYPE_REGION);

    case PARSEOP_OBJECTTYPE_PKG:        /* "PkgObj" */

        return (ACPI_BTYPE_PACKAGE);

    case PARSEOP_OBJECTTYPE_POW:        /* "PowerResObj" */

        return (ACPI_BTYPE_POWER);

    case PARSEOP_OBJECTTYPE_STR:        /* "StrObj" */

        return (ACPI_BTYPE_STRING);

    case PARSEOP_OBJECTTYPE_THZ:        /* "ThermalZoneObj" */

        return (ACPI_BTYPE_THERMAL);

    case PARSEOP_OBJECTTYPE_UNK:        /* "UnknownObj" */

        return (ACPI_BTYPE_OBJECTS_AND_REFS);

    default:

        return (0);
    }
}