#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_9__ {int /*<<< orphan*/  ExternalName; } ;
struct TYPE_10__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_NAME_IO ; 
 scalar_t__ ACPI_RESOURCE_NAME_MEMORY24 ; 
 scalar_t__ ACPI_UINT16_MAX ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_ALIGNMENT ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_LENGTH ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_MIN_MAX ; 
 int /*<<< orphan*/  ASL_MSG_NULL_DESCRIPTOR ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ AslGbl_NoResourceChecking ; 

void
RsSmallAddressCheck (
    UINT8                   Type,
    UINT32                  Minimum,
    UINT32                  Maximum,
    UINT32                  Length,
    UINT32                  Alignment,
    ACPI_PARSE_OBJECT       *MinOp,
    ACPI_PARSE_OBJECT       *MaxOp,
    ACPI_PARSE_OBJECT       *LengthOp,
    ACPI_PARSE_OBJECT       *AlignOp,
    ACPI_PARSE_OBJECT       *Op)
{

    if (AslGbl_NoResourceChecking)
    {
        return;
    }

    /*
     * Check for a so-called "null descriptor". These are descriptors that are
     * created with most fields set to zero. The intent is that the descriptor
     * will be updated/completed at runtime via a BufferField.
     *
     * If the descriptor does NOT have a resource tag, it cannot be referenced
     * by a BufferField and we will flag this as an error. Conversely, if
     * the descriptor has a resource tag, we will assume that a BufferField
     * will be used to dynamically update it, so no error.
     *
     * A possible enhancement to this check would be to verify that in fact
     * a BufferField is created using the resource tag, and perhaps even
     * verify that a Store is performed to the BufferField.
     *
     * Note: for these descriptors, Alignment is allowed to be zero
     */
    if (!Minimum && !Maximum && !Length)
    {
        if (!Op->Asl.ExternalName)
        {
            /* No resource tag. Descriptor is fixed and is also illegal */

            AslError (ASL_ERROR, ASL_MSG_NULL_DESCRIPTOR, Op, NULL);
        }

        return;
    }

    /*
     * Range checks for Memory24 and Memory32.
     * IO descriptor has different definition of min/max, don't check.
     */
    if (Type != ACPI_RESOURCE_NAME_IO)
    {
        /* Basic checks on Min/Max/Length */

        if (Minimum > Maximum)
        {
            AslError (ASL_ERROR, ASL_MSG_INVALID_MIN_MAX, MinOp, NULL);
        }
        else if (Length > (Maximum - Minimum + 1))
        {
            AslError (ASL_ERROR, ASL_MSG_INVALID_LENGTH, LengthOp, NULL);
        }

        /* Special case for Memory24, min/max values are compressed */

        if (Type == ACPI_RESOURCE_NAME_MEMORY24)
        {
            if (!Alignment) /* Alignment==0 means 64K alignment */
            {
                Alignment = ACPI_UINT16_MAX + 1;
            }

            Minimum <<= 8;
            Maximum <<= 8;
        }
    }

    /* Alignment of zero is not in ACPI spec, but is used to mean byte acc */

    if (!Alignment)
    {
        Alignment = 1;
    }

    /* Addresses must be an exact multiple of the alignment value */

    if (Minimum % Alignment)
    {
        AslError (ASL_ERROR, ASL_MSG_ALIGNMENT, MinOp, NULL);
    }
    if (Maximum % Alignment)
    {
        AslError (ASL_ERROR, ASL_MSG_ALIGNMENT, MaxOp, NULL);
    }
}