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
 int ACPI_BTYPE_ALL_OBJECTS ; 
 int ACPI_BTYPE_BUFFER ; 
 int ACPI_BTYPE_COMPUTE_DATA ; 
 int ACPI_BTYPE_DATA ; 
 int ACPI_BTYPE_DATA_REFERENCE ; 
 int ACPI_BTYPE_DDB_HANDLE ; 
 int ACPI_BTYPE_DEBUG_OBJECT ; 
 int ACPI_BTYPE_DEVICE_OBJECTS ; 
 int ACPI_BTYPE_EVENT ; 
 int ACPI_BTYPE_FIELD_UNIT ; 
 int ACPI_BTYPE_INTEGER ; 
 int ACPI_BTYPE_MUTEX ; 
 int ACPI_BTYPE_NAMED_REFERENCE ; 
 int ACPI_BTYPE_OBJECTS_AND_REFS ; 
 int ACPI_BTYPE_PACKAGE ; 
 int ACPI_BTYPE_REFERENCE_OBJECT ; 
 int ACPI_BTYPE_REGION ; 
 int ACPI_BTYPE_STRING ; 
#define  ARGI_ANYTYPE 150 
#define  ARGI_BUFFER 149 
#define  ARGI_BUFFER_OR_STRING 148 
#define  ARGI_COMPLEXOBJ 147 
#define  ARGI_COMPUTEDATA 146 
#define  ARGI_DATAOBJECT 145 
#define  ARGI_DATAREFOBJ 144 
#define  ARGI_DDBHANDLE 143 
#define  ARGI_DEVICE_REF 142 
#define  ARGI_EVENT 141 
#define  ARGI_FIXED_TARGET 140 
#define  ARGI_INTEGER 139 
#define  ARGI_INTEGER_REF 138 
#define  ARGI_MUTEX 137 
#define  ARGI_OBJECT_REF 136 
#define  ARGI_PACKAGE 135 
#define  ARGI_REFERENCE 134 
#define  ARGI_REF_OR_STRING 133 
#define  ARGI_REGION_OR_BUFFER 132 
#define  ARGI_SIMPLE_TARGET 131 
#define  ARGI_STORE_TARGET 130 
#define  ARGI_STRING 129 
#define  ARGI_TARGETREF 128 

UINT32
AnMapArgTypeToBtype (
    UINT32                  ArgType)
{

    switch (ArgType)
    {
    /* Simple types */

    case ARGI_ANYTYPE:

        return (ACPI_BTYPE_OBJECTS_AND_REFS);

    case ARGI_PACKAGE:

        return (ACPI_BTYPE_PACKAGE);

    case ARGI_EVENT:

        return (ACPI_BTYPE_EVENT);

    case ARGI_MUTEX:

        return (ACPI_BTYPE_MUTEX);

    case ARGI_DDBHANDLE:
        /*
         * DDBHandleObject := SuperName
         * ACPI_BTYPE_REFERENCE_OBJECT:
         *      Index reference as parameter of Load/Unload
         */
        return (ACPI_BTYPE_DDB_HANDLE | ACPI_BTYPE_REFERENCE_OBJECT);

    /* Interchangeable types */
    /*
     * Source conversion rules:
     * Integer, String, and Buffer are all interchangeable
     */
    case ARGI_INTEGER:
    case ARGI_STRING:
    case ARGI_BUFFER:
    case ARGI_BUFFER_OR_STRING:
    case ARGI_COMPUTEDATA:

        return (ACPI_BTYPE_COMPUTE_DATA);

    /* References */

    case ARGI_INTEGER_REF:

        return (ACPI_BTYPE_INTEGER);

    case ARGI_OBJECT_REF:

        return (ACPI_BTYPE_ALL_OBJECTS);

    case ARGI_DEVICE_REF:

        return (ACPI_BTYPE_DEVICE_OBJECTS);

    case ARGI_REFERENCE:

        return (ACPI_BTYPE_NAMED_REFERENCE); /* Name or Namestring */

    case ARGI_TARGETREF:

        /*
         * Target operand for most math and logic operators.
         * Package objects not allowed as target.
         */
        return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_DEBUG_OBJECT |
            ACPI_BTYPE_REFERENCE_OBJECT);

    case ARGI_STORE_TARGET:

        /* Special target for Store(), includes packages */

        return (ACPI_BTYPE_DATA | ACPI_BTYPE_DEBUG_OBJECT |
            ACPI_BTYPE_REFERENCE_OBJECT);

    case ARGI_FIXED_TARGET:
    case ARGI_SIMPLE_TARGET:

        return (ACPI_BTYPE_OBJECTS_AND_REFS);

    /* Complex types */

    case ARGI_DATAOBJECT:
        /*
         * Buffer, string, package or reference to a Op -
         * Used only by SizeOf operator
         */
        return (ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER |
            ACPI_BTYPE_PACKAGE | ACPI_BTYPE_REFERENCE_OBJECT);

    case ARGI_COMPLEXOBJ:

        /* Buffer, String, or package */

        return (ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER |
            ACPI_BTYPE_PACKAGE);

    case ARGI_REF_OR_STRING:

        /* Used by DeRefOf operator only */

        return (ACPI_BTYPE_STRING | ACPI_BTYPE_REFERENCE_OBJECT);

    case ARGI_REGION_OR_BUFFER:

        /* Used by Load() only. Allow buffers in addition to regions/fields */

        return (ACPI_BTYPE_REGION | ACPI_BTYPE_BUFFER |
            ACPI_BTYPE_FIELD_UNIT);

    case ARGI_DATAREFOBJ:

        /* Used by Store() only, as the source operand */

        return (ACPI_BTYPE_DATA_REFERENCE | ACPI_BTYPE_REFERENCE_OBJECT);

    default:

        break;
    }

    return (ACPI_BTYPE_OBJECTS_AND_REFS);
}