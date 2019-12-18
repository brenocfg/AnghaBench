#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_9__ {scalar_t__ Integer; } ;
struct TYPE_10__ {scalar_t__ ParseOpcode; TYPE_1__ Value; TYPE_3__* Child; } ;
struct TYPE_11__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RESTAG_VENDORDATA ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_BUFFER_LENGTH ; 
 int /*<<< orphan*/  ASL_MSG_LIST_LENGTH_LONG ; 
 int /*<<< orphan*/  ASL_MSG_LIST_LENGTH_SHORT ; 
 int /*<<< orphan*/  ASL_MSG_SYNTAX ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARSEOP_DEFAULT_ARG ; 
 TYPE_3__* RsCompleteNodeAndGetNext (TYPE_3__*) ; 
 int /*<<< orphan*/  RsCreateByteField (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
RsGetVendorData (
    ACPI_PARSE_OBJECT       *InitializerOp,
    UINT8                   *VendorData,
    ACPI_SIZE               DescriptorOffset)
{
    ACPI_PARSE_OBJECT       *BufferOp;
    UINT32                  SpecifiedLength = ACPI_UINT32_MAX;
    UINT16                  ActualLength = 0;


    /* Vendor Data field is always optional */

    if (InitializerOp->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)
    {
        return (FALSE);
    }

    BufferOp = InitializerOp->Asl.Child;
    if (!BufferOp)
    {
        AslError (ASL_ERROR, ASL_MSG_SYNTAX, InitializerOp, "");
        return (FALSE);
    }

    /* First child is the optional buffer length (WORD) */

    if (BufferOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
    {
        SpecifiedLength = (UINT16) BufferOp->Asl.Value.Integer;
    }

    /* Insert field tag _VEN */

    RsCreateByteField (InitializerOp, ACPI_RESTAG_VENDORDATA,
        (UINT16) DescriptorOffset);

    /* Walk the list of buffer initializers (each is one byte) */

    BufferOp = RsCompleteNodeAndGetNext (BufferOp);
    if (BufferOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
    {
        while (BufferOp)
        {
            *VendorData = (UINT8) BufferOp->Asl.Value.Integer;
            VendorData++;
            ActualLength++;
            BufferOp = RsCompleteNodeAndGetNext (BufferOp);
        }
    }

    /* Length validation. Buffer cannot be of zero length */

    if ((SpecifiedLength == 0) ||
        ((SpecifiedLength == ACPI_UINT32_MAX) && (ActualLength == 0)))
    {
        AslError (ASL_ERROR, ASL_MSG_BUFFER_LENGTH, InitializerOp, NULL);
        return (FALSE);
    }

    if (SpecifiedLength != ACPI_UINT32_MAX)
    {
        /* ActualLength > SpecifiedLength -> error */

        if (ActualLength > SpecifiedLength)
        {
            AslError (ASL_ERROR, ASL_MSG_LIST_LENGTH_LONG, InitializerOp, NULL);
            return (FALSE);
        }

        /* ActualLength < SpecifiedLength -> remark */

        else if (ActualLength < SpecifiedLength)
        {
            AslError (ASL_REMARK, ASL_MSG_LIST_LENGTH_SHORT, InitializerOp, NULL);
            return (FALSE);
        }
    }

    return (TRUE);
}