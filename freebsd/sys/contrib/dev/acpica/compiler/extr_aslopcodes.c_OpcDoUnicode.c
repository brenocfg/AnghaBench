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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {int Integer; int /*<<< orphan*/ * Buffer; scalar_t__ String; } ;
struct TYPE_8__ {int AmlLength; TYPE_3__* Child; int /*<<< orphan*/  ParseOpcode; int /*<<< orphan*/  AmlOpcode; TYPE_1__ Value; TYPE_3__* Next; int /*<<< orphan*/  CompileFlags; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_DWORD_OP ; 
 int /*<<< orphan*/  AML_RAW_DATA_BUFFER ; 
 int /*<<< orphan*/  OP_COMPILE_TIME_CONST ; 
 int /*<<< orphan*/  OpcSetOptimalIntegerSize (TYPE_3__*) ; 
 int /*<<< orphan*/  PARSEOP_BUFFER ; 
 int /*<<< orphan*/  PARSEOP_INTEGER ; 
 int /*<<< orphan*/  PARSEOP_RAW_DATA ; 
 scalar_t__* UtLocalCalloc (int) ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_3__*) ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static void
OpcDoUnicode (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *InitializerOp;
    UINT32                  Length;
    UINT32                  Count;
    UINT32                  i;
    UINT8                   *AsciiString;
    UINT16                  *UnicodeString;
    ACPI_PARSE_OBJECT       *BufferLengthOp;


    /* Change op into a buffer object */

    Op->Asl.CompileFlags &= ~OP_COMPILE_TIME_CONST;
    Op->Asl.ParseOpcode = PARSEOP_BUFFER;
    UtSetParseOpName (Op);

    /* Buffer Length is first, followed by the string */

    BufferLengthOp = Op->Asl.Child;
    InitializerOp = BufferLengthOp->Asl.Next;

    AsciiString = (UINT8 *) InitializerOp->Asl.Value.String;

    /* Create a new buffer for the Unicode string */

    Count = strlen (InitializerOp->Asl.Value.String) + 1;
    Length = Count * sizeof (UINT16);
    UnicodeString = UtLocalCalloc (Length);

    /* Convert to Unicode string (including null terminator) */

    for (i = 0; i < Count; i++)
    {
        UnicodeString[i] = (UINT16) AsciiString[i];
    }

    /*
     * Just set the buffer size node to be the buffer length, regardless
     * of whether it was previously an integer or a default_arg placeholder
     */
    BufferLengthOp->Asl.ParseOpcode = PARSEOP_INTEGER;
    BufferLengthOp->Asl.AmlOpcode = AML_DWORD_OP;
    BufferLengthOp->Asl.Value.Integer = Length;
    UtSetParseOpName (BufferLengthOp);

    (void) OpcSetOptimalIntegerSize (BufferLengthOp);

    /* The Unicode string is a raw data buffer */

    InitializerOp->Asl.Value.Buffer = (UINT8 *) UnicodeString;
    InitializerOp->Asl.AmlOpcode = AML_RAW_DATA_BUFFER;
    InitializerOp->Asl.AmlLength = Length;
    InitializerOp->Asl.ParseOpcode = PARSEOP_RAW_DATA;
    InitializerOp->Asl.Child = NULL;
    UtSetParseOpName (InitializerOp);
}