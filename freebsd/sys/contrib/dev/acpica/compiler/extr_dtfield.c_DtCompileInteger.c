#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT64 ;
typedef  int UINT32 ;
struct TYPE_6__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ DT_FIELD ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_FORMAT_UINT64 (int) ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  ASL_MSG_INTEGER_SIZE ; 
 int /*<<< orphan*/  ASL_MSG_RESERVED_VALUE ; 
 int /*<<< orphan*/  ASL_MSG_ZERO_VALUE ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 char* AslGbl_MsgBuffer ; 
 int DT_NON_ZERO ; 
 int /*<<< orphan*/  DtError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  DtFatal (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  DtResolveIntegerExpression (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void
DtCompileInteger (
    UINT8                   *Buffer,
    DT_FIELD                *Field,
    UINT32                  ByteLength,
    UINT8                   Flags)
{
    UINT64                  Value;
    UINT64                  MaxValue;
    ACPI_STATUS             Status;


    /* Output buffer byte length must be in range 1-8 */

    if ((ByteLength > 8) || (ByteLength == 0))
    {
        DtFatal (ASL_MSG_COMPILER_INTERNAL, Field,
            "Invalid internal Byte length");
        return;
    }

    /* Resolve integer expression to a single integer value */

    Status = DtResolveIntegerExpression (Field, &Value);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    /*
     * Ensure that reserved fields are set properly. Note: uses
     * the DT_NON_ZERO flag to indicate that the reserved value
     * must be exactly one. Otherwise, the value must be zero.
     * This is sufficient for now.
     */

    /* TBD: Should use a flag rather than compare "Reserved" */

    if (!strcmp (Field->Name, "Reserved"))
    {
        if (Flags & DT_NON_ZERO)
        {
            if (Value != 1)
            {
                DtError (ASL_WARNING, ASL_MSG_RESERVED_VALUE, Field,
                    "Must be one, setting to one");
                Value = 1;
            }
        }
        else if (Value != 0)
        {
            DtError (ASL_WARNING, ASL_MSG_RESERVED_VALUE, Field,
                "Must be zero, setting to zero");
            Value = 0;
        }
    }

    /* Check if the value must be non-zero */

    else if ((Flags & DT_NON_ZERO) && (Value == 0))
    {
        DtError (ASL_ERROR, ASL_MSG_ZERO_VALUE, Field, NULL);
    }

    /*
     * Generate the maximum value for the data type (ByteLength)
     * Note: construct chosen for maximum portability
     */
    MaxValue = ((UINT64) (-1)) >> (64 - (ByteLength * 8));

    /* Validate that the input value is within range of the target */

    if (Value > MaxValue)
    {
        sprintf (AslGbl_MsgBuffer, "%8.8X%8.8X - max %u bytes",
            ACPI_FORMAT_UINT64 (Value), ByteLength);
        DtError (ASL_ERROR, ASL_MSG_INTEGER_SIZE, Field, AslGbl_MsgBuffer);
    }

    memcpy (Buffer, &Value, ByteLength);
    return;
}