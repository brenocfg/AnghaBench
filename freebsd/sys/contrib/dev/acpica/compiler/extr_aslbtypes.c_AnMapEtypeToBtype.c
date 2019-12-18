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
typedef  int UINT32 ;

/* Variables and functions */
 int ACPI_BTYPE_BUFFER_FIELD ; 
 int ACPI_BTYPE_COMPUTE_DATA ; 
 int ACPI_BTYPE_DDB_HANDLE ; 
 int ACPI_BTYPE_FIELD_UNIT ; 
 int ACPI_BTYPE_INTEGER ; 
 int ACPI_BTYPE_OBJECTS_AND_REFS ; 
 int ACPI_BTYPE_PACKAGE ; 
 int ACPI_BTYPE_REFERENCE_OBJECT ; 
 int ACPI_TYPE_ANY ; 
#define  ACPI_TYPE_BUFFER 141 
#define  ACPI_TYPE_BUFFER_FIELD 140 
#define  ACPI_TYPE_DDB_HANDLE 139 
#define  ACPI_TYPE_DEBUG_OBJECT 138 
 int ACPI_TYPE_EXTERNAL_MAX ; 
#define  ACPI_TYPE_FIELD_UNIT 137 
#define  ACPI_TYPE_INTEGER 136 
#define  ACPI_TYPE_LOCAL_ALIAS 135 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 134 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 133 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 132 
#define  ACPI_TYPE_LOCAL_RESOURCE 131 
#define  ACPI_TYPE_LOCAL_RESOURCE_FIELD 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static UINT32
AnMapEtypeToBtype (
    UINT32                  Etype)
{

    if (Etype == ACPI_TYPE_ANY)
    {
        return (ACPI_BTYPE_OBJECTS_AND_REFS);
    }

    /* Try the standard ACPI data types */

    if (Etype <= ACPI_TYPE_EXTERNAL_MAX)
    {
        /*
         * This switch statement implements the allowed operand conversion
         * rules as per the "ASL Data Types" section of the ACPI
         * specification.
         */
        switch (Etype)
        {
        case ACPI_TYPE_INTEGER:

            return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_DDB_HANDLE);

        case ACPI_TYPE_STRING:
        case ACPI_TYPE_BUFFER:

            return (ACPI_BTYPE_COMPUTE_DATA);

        case ACPI_TYPE_PACKAGE:

            return (ACPI_BTYPE_PACKAGE);

        case ACPI_TYPE_FIELD_UNIT:

            return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_FIELD_UNIT);

        case ACPI_TYPE_BUFFER_FIELD:

            return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_BUFFER_FIELD);

        case ACPI_TYPE_DDB_HANDLE:

            return (ACPI_BTYPE_INTEGER | ACPI_BTYPE_DDB_HANDLE);

        case ACPI_TYPE_DEBUG_OBJECT:

            /* Cannot be used as a source operand */

            return (0);

        default:

            return (1 << (Etype - 1));
        }
    }

    /* Try the internal data types */

    switch (Etype)
    {
    case ACPI_TYPE_LOCAL_REGION_FIELD:
    case ACPI_TYPE_LOCAL_BANK_FIELD:
    case ACPI_TYPE_LOCAL_INDEX_FIELD:

        /* Named fields can be either Integer/Buffer/String */

        return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_FIELD_UNIT);

    case ACPI_TYPE_LOCAL_ALIAS:

        return (ACPI_BTYPE_INTEGER);


    case ACPI_TYPE_LOCAL_RESOURCE:
    case ACPI_TYPE_LOCAL_RESOURCE_FIELD:

        return (ACPI_BTYPE_REFERENCE_OBJECT);

    default:

        printf ("Unhandled encoded type: %X\n", Etype);
        return (0);
    }
}