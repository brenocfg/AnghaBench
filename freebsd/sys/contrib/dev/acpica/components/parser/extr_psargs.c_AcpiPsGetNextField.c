#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int UINT16 ;
struct TYPE_20__ {int Integer; int /*<<< orphan*/  Name; void* Size; } ;
struct TYPE_21__ {TYPE_3__ Value; int /*<<< orphan*/ * InlineComment; int /*<<< orphan*/ * NameComment; } ;
struct TYPE_18__ {int Size; } ;
struct TYPE_19__ {int* Data; TYPE_1__ Value; } ;
struct TYPE_23__ {TYPE_4__ Common; TYPE_2__ Named; } ;
struct TYPE_22__ {int* Aml; } ;
typedef  TYPE_5__ ACPI_PARSE_STATE ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GET16 (int*) ; 
 int ACPI_GET32 (int*) ; 
 int ACPI_GET8 (int*) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (int*,int*) ; 
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 int AML_BUFFER_OP ; 
#define  AML_BYTE_OP 139 
#define  AML_DWORD_OP 138 
#define  AML_FIELD_ACCESS_OP 137 
#define  AML_FIELD_CONNECTION_OP 136 
#define  AML_FIELD_EXT_ACCESS_OP 135 
#define  AML_FIELD_OFFSET_OP 134 
#define  AML_INT_ACCESSFIELD_OP 133 
 int AML_INT_BYTELIST_OP ; 
#define  AML_INT_CONNECTION_OP 132 
#define  AML_INT_EXTACCESSFIELD_OP 131 
#define  AML_INT_NAMEDFIELD_OP 130 
 int AML_INT_NAMEPATH_OP ; 
#define  AML_INT_RESERVEDFIELD_OP 129 
#define  AML_WORD_OP 128 
 int /*<<< orphan*/  ASL_CV_CAPTURE_COMMENTS_ONLY (TYPE_5__*) ; 
 int /*<<< orphan*/ * AcpiGbl_CurrentInlineComment ; 
 TYPE_6__* AcpiPsAllocOp (int,int*) ; 
 int /*<<< orphan*/  AcpiPsAppendArg (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiPsFreeOp (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiPsGetNextNamestring (TYPE_5__*) ; 
 void* AcpiPsGetNextPackageLength (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiPsSetName (TYPE_6__*,int) ; 
 int /*<<< orphan*/  PsGetNextField ; 
 int /*<<< orphan*/  return_PTR (TYPE_6__*) ; 

__attribute__((used)) static ACPI_PARSE_OBJECT *
AcpiPsGetNextField (
    ACPI_PARSE_STATE        *ParserState)
{
    UINT8                   *Aml;
    ACPI_PARSE_OBJECT       *Field;
    ACPI_PARSE_OBJECT       *Arg = NULL;
    UINT16                  Opcode;
    UINT32                  Name;
    UINT8                   AccessType;
    UINT8                   AccessAttribute;
    UINT8                   AccessLength;
    UINT32                  PkgLength;
    UINT8                   *PkgEnd;
    UINT32                  BufferLength;


    ACPI_FUNCTION_TRACE (PsGetNextField);


    ASL_CV_CAPTURE_COMMENTS_ONLY (ParserState);
    Aml = ParserState->Aml;

    /* Determine field type */

    switch (ACPI_GET8 (ParserState->Aml))
    {
    case AML_FIELD_OFFSET_OP:

        Opcode = AML_INT_RESERVEDFIELD_OP;
        ParserState->Aml++;
        break;

    case AML_FIELD_ACCESS_OP:

        Opcode = AML_INT_ACCESSFIELD_OP;
        ParserState->Aml++;
        break;

    case AML_FIELD_CONNECTION_OP:

        Opcode = AML_INT_CONNECTION_OP;
        ParserState->Aml++;
        break;

    case AML_FIELD_EXT_ACCESS_OP:

        Opcode = AML_INT_EXTACCESSFIELD_OP;
        ParserState->Aml++;
        break;

    default:

        Opcode = AML_INT_NAMEDFIELD_OP;
        break;
    }

    /* Allocate a new field op */

    Field = AcpiPsAllocOp (Opcode, Aml);
    if (!Field)
    {
        return_PTR (NULL);
    }

    /* Decode the field type */

    ASL_CV_CAPTURE_COMMENTS_ONLY (ParserState);
    switch (Opcode)
    {
    case AML_INT_NAMEDFIELD_OP:

        /* Get the 4-character name */

        ACPI_MOVE_32_TO_32 (&Name, ParserState->Aml);
        AcpiPsSetName (Field, Name);
        ParserState->Aml += ACPI_NAMESEG_SIZE;


        ASL_CV_CAPTURE_COMMENTS_ONLY (ParserState);

#ifdef ACPI_ASL_COMPILER
        /*
         * Because the package length isn't represented as a parse tree object,
         * take comments surrounding this and add to the previously created
         * parse node.
         */
        if (Field->Common.InlineComment)
        {
            Field->Common.NameComment = Field->Common.InlineComment;
        }
        Field->Common.InlineComment  = AcpiGbl_CurrentInlineComment;
        AcpiGbl_CurrentInlineComment = NULL;
#endif

        /* Get the length which is encoded as a package length */

        Field->Common.Value.Size = AcpiPsGetNextPackageLength (ParserState);
        break;


    case AML_INT_RESERVEDFIELD_OP:

        /* Get the length which is encoded as a package length */

        Field->Common.Value.Size = AcpiPsGetNextPackageLength (ParserState);
        break;


    case AML_INT_ACCESSFIELD_OP:
    case AML_INT_EXTACCESSFIELD_OP:

        /*
         * Get AccessType and AccessAttrib and merge into the field Op
         * AccessType is first operand, AccessAttribute is second. stuff
         * these bytes into the node integer value for convenience.
         */

        /* Get the two bytes (Type/Attribute) */

        AccessType = ACPI_GET8 (ParserState->Aml);
        ParserState->Aml++;
        AccessAttribute = ACPI_GET8 (ParserState->Aml);
        ParserState->Aml++;

        Field->Common.Value.Integer = (UINT8) AccessType;
        Field->Common.Value.Integer |= (UINT16) (AccessAttribute << 8);

        /* This opcode has a third byte, AccessLength */

        if (Opcode == AML_INT_EXTACCESSFIELD_OP)
        {
            AccessLength = ACPI_GET8 (ParserState->Aml);
            ParserState->Aml++;

            Field->Common.Value.Integer |= (UINT32) (AccessLength << 16);
        }
        break;


    case AML_INT_CONNECTION_OP:

        /*
         * Argument for Connection operator can be either a Buffer
         * (resource descriptor), or a NameString.
         */
        Aml = ParserState->Aml;
        if (ACPI_GET8 (ParserState->Aml) == AML_BUFFER_OP)
        {
            ParserState->Aml++;

            ASL_CV_CAPTURE_COMMENTS_ONLY (ParserState);
            PkgEnd = ParserState->Aml;
            PkgLength = AcpiPsGetNextPackageLength (ParserState);
            PkgEnd += PkgLength;

            ASL_CV_CAPTURE_COMMENTS_ONLY (ParserState);
            if (ParserState->Aml < PkgEnd)
            {
                /* Non-empty list */

                Arg = AcpiPsAllocOp (AML_INT_BYTELIST_OP, Aml);
                if (!Arg)
                {
                    AcpiPsFreeOp (Field);
                    return_PTR (NULL);
                }

                /* Get the actual buffer length argument */

                Opcode = ACPI_GET8 (ParserState->Aml);
                ParserState->Aml++;

                ASL_CV_CAPTURE_COMMENTS_ONLY (ParserState);
                switch (Opcode)
                {
                case AML_BYTE_OP:       /* AML_BYTEDATA_ARG */

                    BufferLength = ACPI_GET8 (ParserState->Aml);
                    ParserState->Aml += 1;
                    break;

                case AML_WORD_OP:       /* AML_WORDDATA_ARG */

                    BufferLength = ACPI_GET16 (ParserState->Aml);
                    ParserState->Aml += 2;
                    break;

                case AML_DWORD_OP:      /* AML_DWORDATA_ARG */

                    BufferLength = ACPI_GET32 (ParserState->Aml);
                    ParserState->Aml += 4;
                    break;

                default:

                    BufferLength = 0;
                    break;
                }

                /* Fill in bytelist data */

                ASL_CV_CAPTURE_COMMENTS_ONLY (ParserState);
                Arg->Named.Value.Size = BufferLength;
                Arg->Named.Data = ParserState->Aml;
            }

            /* Skip to End of byte data */

            ParserState->Aml = PkgEnd;
        }
        else
        {
            Arg = AcpiPsAllocOp (AML_INT_NAMEPATH_OP, Aml);
            if (!Arg)
            {
                AcpiPsFreeOp (Field);
                return_PTR (NULL);
            }

            /* Get the Namestring argument */

            Arg->Common.Value.Name = AcpiPsGetNextNamestring (ParserState);
        }

        /* Link the buffer/namestring to parent (CONNECTION_OP) */

        AcpiPsAppendArg (Field, Arg);
        break;


    default:

        /* Opcode was set in previous switch */
        break;
    }

    return_PTR (Field);
}