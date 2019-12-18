#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_9__ {scalar_t__ Integer; } ;
struct TYPE_10__ {int ParseOpcode; TYPE_2__ Value; TYPE_4__* Next; TYPE_4__* Child; TYPE_1__* Node; } ;
struct TYPE_11__ {TYPE_3__ Asl; } ;
struct TYPE_8__ {TYPE_4__* Op; } ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_ROUND_BITS_DOWN_TO_BYTES (scalar_t__) ; 
 int /*<<< orphan*/  ASL_MSG_BUFFER_FIELD_LENGTH ; 
 int /*<<< orphan*/  ASL_MSG_BUFFER_FIELD_OVERFLOW ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AnIsValidBufferConstant (TYPE_4__*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
#define  PARSEOP_CREATEBITFIELD 133 
#define  PARSEOP_CREATEBYTEFIELD 132 
#define  PARSEOP_CREATEDWORDFIELD 131 
#define  PARSEOP_CREATEFIELD 130 
#define  PARSEOP_CREATEQWORDFIELD 129 
#define  PARSEOP_CREATEWORDFIELD 128 

__attribute__((used)) static void
AnValidateCreateBufferField (
    ACPI_PARSE_OBJECT       *CreateBufferFieldOp)
{
    ACPI_PARSE_OBJECT       *TargetBufferOp;
    ACPI_PARSE_OBJECT       *ArgOp;
    UINT32                  TargetBufferLength;
    UINT32                  LastFieldByteIndex;


    /*
     * 1) Get the length of the target buffer
     */
    ArgOp = CreateBufferFieldOp->Asl.Child;     /* Reference to target buffer */

    /*
     * If no attached Node, the target buffer may be something like an
     * ArgX or LocalX and cannot be evaluated at compile time.
     */
    if (!ArgOp->Asl.Node)
    {
        return;
    }

    TargetBufferOp = ArgOp->Asl.Node->Op;
    TargetBufferOp = TargetBufferOp->Asl.Child; /* Target buffer */
    TargetBufferOp = TargetBufferOp->Asl.Next;  /* "Buffer" keyword */
    if (!TargetBufferOp)
    {
        /* Not a statement of the form NAME(XXXX, Buffer.... */

        return;
    }

    /* Get the buffer length argument. It must be an integer constant */

    ArgOp = TargetBufferOp->Asl.Child;
    if (!AnIsValidBufferConstant (ArgOp))
    {
        return;
    }

    TargetBufferLength = (UINT32) ArgOp->Asl.Value.Integer;

    /*
     * 2) Get the value of the buffer index argument. It must be
     * an integer constant.
     */
    ArgOp = CreateBufferFieldOp->Asl.Child;     /* Reference to target buffer */
    ArgOp = ArgOp->Asl.Next;                    /* Buffer Index argument*/
    if (!AnIsValidBufferConstant (ArgOp))
    {
        return;
    }

    LastFieldByteIndex =
        (UINT32) ArgOp->Asl.Value.Integer;      /* Index can be in either bytes or bits */

    /*
     * 3) Get the length of the new buffer field, in bytes. Also,
     * create the final target buffer index for the last byte of the field
     */
    switch (CreateBufferFieldOp->Asl.ParseOpcode)
    {
    case PARSEOP_CREATEBITFIELD:                /* A one bit field */

        LastFieldByteIndex = ACPI_ROUND_BITS_DOWN_TO_BYTES (LastFieldByteIndex);
        break;

    case PARSEOP_CREATEBYTEFIELD:
        break;

    case PARSEOP_CREATEWORDFIELD:

        LastFieldByteIndex += (sizeof (UINT16) - 1);
        break;

    case PARSEOP_CREATEDWORDFIELD:

        LastFieldByteIndex += (sizeof (UINT32) - 1);
        break;

    case PARSEOP_CREATEQWORDFIELD:

        LastFieldByteIndex += (sizeof (UINT64) - 1);
        break;

    case PARSEOP_CREATEFIELD:                   /* Multi-bit field */

        ArgOp = ArgOp->Asl.Next;                /* Length argument, in bits */
        if (!AnIsValidBufferConstant (ArgOp))
        {
            return;
        }

        /* The buffer field length is not allowed to be zero */

        if (ArgOp->Asl.Value.Integer == 0)
        {
            AslError (ASL_WARNING,  ASL_MSG_BUFFER_FIELD_LENGTH, ArgOp, NULL);
            return;
        }

        LastFieldByteIndex +=
            ((UINT32) ArgOp->Asl.Value.Integer - 1);    /* Create final bit index */

        /* Convert bit index to a byte index */

        LastFieldByteIndex = ACPI_ROUND_BITS_DOWN_TO_BYTES (LastFieldByteIndex);
        break;

    default:
        return;
    }

    /*
     * 4) Check for an access (index) beyond the end of the target buffer,
     * or a zero length target buffer.
     */
    if (!TargetBufferLength || (LastFieldByteIndex >= TargetBufferLength))
    {
        AslError (ASL_WARNING, ASL_MSG_BUFFER_FIELD_OVERFLOW, ArgOp, NULL);
    }
}