#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_7__ {int Integer; } ;
struct TYPE_8__ {int ParseOpcode; int AmlLength; int ExtraValue; TYPE_3__* Next; TYPE_1__ Value; TYPE_3__* Child; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  AML_FIELD_ACCESS_ANY 137 
#define  AML_FIELD_ACCESS_BUFFER 136 
#define  AML_FIELD_ACCESS_BYTE 135 
#define  AML_FIELD_ACCESS_DWORD 134 
#define  AML_FIELD_ACCESS_QWORD 133 
#define  AML_FIELD_ACCESS_WORD 132 
 int /*<<< orphan*/  AML_RAW_DATA_BYTE ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_BACKWARDS_OFFSET ; 
 int /*<<< orphan*/  ASL_MSG_OFFSET ; 
 int /*<<< orphan*/  ASL_OPTIMIZATION ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  AslGbl_OptimizeTrivialParseNodes ; 
#define  PARSEOP_ACCESSAS 131 
 void* PARSEOP_DEFAULT_ARG ; 
#define  PARSEOP_NAMESEG 130 
#define  PARSEOP_OFFSET 129 
 int PARSEOP_RAW_DATA ; 
#define  PARSEOP_RESERVED_BYTES 128 

__attribute__((used)) static void
OpnDoFieldCommon (
    ACPI_PARSE_OBJECT       *FieldOp,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;
    ACPI_PARSE_OBJECT       *PkgLengthNode;
    UINT32                  CurrentBitOffset;
    UINT32                  NewBitOffset;
    UINT8                   AccessType;
    UINT8                   LockRule;
    UINT8                   UpdateRule;
    UINT8                   FieldFlags;
    UINT32                  MinimumLength;


    /* AccessType -- not optional, so no need to check for DEFAULT_ARG */

    AccessType = (UINT8) Op->Asl.Value.Integer;
    Op->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;

    /* Set the access type in the parent (field) node for use later */

    FieldOp->Asl.Value.Integer = AccessType;

    /* LockRule -- not optional, so no need to check for DEFAULT_ARG */

    Next = Op->Asl.Next;
    LockRule = (UINT8) Next->Asl.Value.Integer;
    Next->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;

    /* UpdateRule -- not optional, so no need to check for DEFAULT_ARG */

    Next = Next->Asl.Next;
    UpdateRule = (UINT8) Next->Asl.Value.Integer;

    /*
     * Generate the flags byte. The various fields are already
     * in the right bit position via translation from the
     * keywords by the parser.
     */
    FieldFlags = (UINT8) (AccessType | LockRule | UpdateRule);

    /* Use the previous node to be the FieldFlags node */

    /* Set the node to RAW_DATA */

    Next->Asl.Value.Integer = FieldFlags;
    Next->Asl.AmlOpcode = AML_RAW_DATA_BYTE;
    Next->Asl.AmlLength = 1;
    Next->Asl.ParseOpcode = PARSEOP_RAW_DATA;

    /* Process the FieldUnitList */

    Next = Next->Asl.Next;
    CurrentBitOffset = 0;

    while (Next)
    {
        /* Save the offset of this field unit */

        Next->Asl.ExtraValue = CurrentBitOffset;

        switch (Next->Asl.ParseOpcode)
        {
        case PARSEOP_ACCESSAS:

            PkgLengthNode = Next->Asl.Child;
            AccessType = (UINT8) PkgLengthNode->Asl.Value.Integer;

            /* Nothing additional to do */
            break;

        case PARSEOP_OFFSET:

            /* New offset into the field */

            PkgLengthNode = Next->Asl.Child;
            NewBitOffset = ((UINT32) PkgLengthNode->Asl.Value.Integer) * 8;

            /*
             * Examine the specified offset in relation to the
             * current offset counter.
             */
            if (NewBitOffset < CurrentBitOffset)
            {
                /*
                 * Not allowed to specify a backwards offset!
                 * Issue error and ignore this node.
                 */
                AslError (ASL_ERROR, ASL_MSG_BACKWARDS_OFFSET, PkgLengthNode,
                    NULL);
                Next->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
                PkgLengthNode->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
            }
            else if (NewBitOffset == CurrentBitOffset)
            {
                /*
                 * This Offset() operator is redundant and not needed,
                 * because the offset value is the same as the current
                 * offset.
                 */
                AslError (ASL_REMARK, ASL_MSG_OFFSET, PkgLengthNode, NULL);

                if (AslGbl_OptimizeTrivialParseNodes)
                {
                    /*
                     * Optimize this Offset() operator by removing/ignoring
                     * it. Set the related nodes to default.
                     */
                    Next->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
                    PkgLengthNode->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;

                    AslError (ASL_OPTIMIZATION, ASL_MSG_OFFSET, PkgLengthNode,
                        "Optimizer has removed statement");
                }
                else
                {
                    /* Optimization is disabled, treat as a valid Offset */

                    PkgLengthNode->Asl.Value.Integer =
                        NewBitOffset - CurrentBitOffset;
                    CurrentBitOffset = NewBitOffset;
                }
            }
            else
            {
                /*
                 * Valid new offset - set the value to be inserted into the AML
                 * and update the offset counter.
                 */
                PkgLengthNode->Asl.Value.Integer =
                    NewBitOffset - CurrentBitOffset;
                CurrentBitOffset = NewBitOffset;
            }
            break;

        case PARSEOP_NAMESEG:
        case PARSEOP_RESERVED_BYTES:

            /* Named or reserved field entry */

            PkgLengthNode = Next->Asl.Child;
            NewBitOffset = (UINT32) PkgLengthNode->Asl.Value.Integer;
            CurrentBitOffset += NewBitOffset;

            if ((NewBitOffset == 0) &&
                (Next->Asl.ParseOpcode == PARSEOP_RESERVED_BYTES) &&
                AslGbl_OptimizeTrivialParseNodes)
            {
                /*
                 * Unnamed field with a bit length of zero. We can
                 * safely just ignore this. However, we will not ignore
                 * a named field of zero length, we don't want to just
                 * toss out a name.
                 */
                Next->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
                PkgLengthNode->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
                break;
            }

            /* Save the current AccessAs value for error checking later */

            switch (AccessType)
            {
                case AML_FIELD_ACCESS_ANY:
                case AML_FIELD_ACCESS_BYTE:
                case AML_FIELD_ACCESS_BUFFER:
                default:

                    MinimumLength = 8;
                    break;

                case AML_FIELD_ACCESS_WORD:
                    MinimumLength = 16;
                    break;

                case AML_FIELD_ACCESS_DWORD:
                    MinimumLength = 32;
                    break;

                case AML_FIELD_ACCESS_QWORD:
                    MinimumLength = 64;
                    break;
            }

            PkgLengthNode->Asl.ExtraValue = MinimumLength;
            break;

        default:

            /* All supported field opcodes must appear above */

            break;
        }

        /* Move on to next entry in the field list */

        Next = Next->Asl.Next;
    }
}