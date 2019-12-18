#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_3__ {int Length; char* Pointer; } ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  void ACPI_OPERAND_OBJECT ;
typedef  void ACPI_NAMESPACE_NODE ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
#define  ACPI_DESC_TYPE_NAMED 130 
#define  ACPI_DESC_TYPE_OPERAND 129 
#define  ACPI_DESC_TYPE_PARSER 128 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME_NO_TRAILING ; 
 int const ACPI_GET_DESCRIPTOR_TYPE (void*) ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AcpiDbDumpParserDescriptor (int /*<<< orphan*/ *) ; 
 void* AcpiDbGetPointer (char*) ; 
 void* AcpiDbLocalNsLookup (char*) ; 
 int /*<<< orphan*/  AcpiExDumpNamespaceNode (void*,int) ; 
 int /*<<< orphan*/  AcpiExDumpObjectDescriptor (void*,int) ; 
 int /*<<< orphan*/  AcpiGetName (void*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* AcpiNsGetAttachedObject (void*) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 scalar_t__ AcpiOsReadable (void*,int) ; 
 int /*<<< orphan*/  AcpiUtDebugDumpBuffer (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 int DB_BYTE_DISPLAY ; 
 int DB_DWORD_DISPLAY ; 
 int DB_QWORD_DISPLAY ; 
 int DB_WORD_DISPLAY ; 

void
AcpiDbDecodeAndDisplayObject (
    char                    *Target,
    char                    *OutputType)
{
    void                    *ObjPtr;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    UINT32                  Display = DB_BYTE_DISPLAY;
    char                    Buffer[80];
    ACPI_BUFFER             RetBuf;
    ACPI_STATUS             Status;
    UINT32                  Size;


    if (!Target)
    {
        return;
    }

    /* Decode the output type */

    if (OutputType)
    {
        AcpiUtStrupr (OutputType);
        if (OutputType[0] == 'W')
        {
            Display = DB_WORD_DISPLAY;
        }
        else if (OutputType[0] == 'D')
        {
            Display = DB_DWORD_DISPLAY;
        }
        else if (OutputType[0] == 'Q')
        {
            Display = DB_QWORD_DISPLAY;
        }
    }

    RetBuf.Length = sizeof (Buffer);
    RetBuf.Pointer = Buffer;

    /* Differentiate between a number and a name */

    if ((Target[0] >= 0x30) && (Target[0] <= 0x39))
    {
        ObjPtr = AcpiDbGetPointer (Target);
        if (!AcpiOsReadable (ObjPtr, 16))
        {
            AcpiOsPrintf (
                "Address %p is invalid in this address space\n",
                ObjPtr);
            return;
        }

        /* Decode the object type */

        switch (ACPI_GET_DESCRIPTOR_TYPE (ObjPtr))
        {
        case ACPI_DESC_TYPE_NAMED:

            /* This is a namespace Node */

            if (!AcpiOsReadable (ObjPtr, sizeof (ACPI_NAMESPACE_NODE)))
            {
                AcpiOsPrintf (
                    "Cannot read entire Named object at address %p\n",
                    ObjPtr);
                return;
            }

            Node = ObjPtr;
            goto DumpNode;

        case ACPI_DESC_TYPE_OPERAND:

            /* This is a ACPI OPERAND OBJECT */

            if (!AcpiOsReadable (ObjPtr, sizeof (ACPI_OPERAND_OBJECT)))
            {
                AcpiOsPrintf (
                    "Cannot read entire ACPI object at address %p\n",
                    ObjPtr);
                return;
            }

            AcpiUtDebugDumpBuffer (ObjPtr, sizeof (ACPI_OPERAND_OBJECT),
                Display, ACPI_UINT32_MAX);
            AcpiExDumpObjectDescriptor (ObjPtr, 1);
            break;

        case ACPI_DESC_TYPE_PARSER:

            /* This is a Parser Op object */

            if (!AcpiOsReadable (ObjPtr, sizeof (ACPI_PARSE_OBJECT)))
            {
                AcpiOsPrintf (
                    "Cannot read entire Parser object at address %p\n",
                    ObjPtr);
                return;
            }

            AcpiUtDebugDumpBuffer (ObjPtr, sizeof (ACPI_PARSE_OBJECT),
                Display, ACPI_UINT32_MAX);
            AcpiDbDumpParserDescriptor ((ACPI_PARSE_OBJECT *) ObjPtr);
            break;

        default:

            /* Is not a recognizable object */

            AcpiOsPrintf (
                "Not a known ACPI internal object, descriptor type %2.2X\n",
                ACPI_GET_DESCRIPTOR_TYPE (ObjPtr));

            Size = 16;
            if (AcpiOsReadable (ObjPtr, 64))
            {
                Size = 64;
            }

            /* Just dump some memory */

            AcpiUtDebugDumpBuffer (ObjPtr, Size, Display, ACPI_UINT32_MAX);
            break;
        }

        return;
    }

    /* The parameter is a name string that must be resolved to a Named obj */

    Node = AcpiDbLocalNsLookup (Target);
    if (!Node)
    {
        return;
    }


DumpNode:
    /* Now dump the NS node */

    Status = AcpiGetName (Node, ACPI_FULL_PATHNAME_NO_TRAILING, &RetBuf);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not convert name to pathname\n");
    }

    else
    {
        AcpiOsPrintf ("Object %p: Namespace Node - Pathname: %s\n",
            Node, (char *) RetBuf.Pointer);
    }

    if (!AcpiOsReadable (Node, sizeof (ACPI_NAMESPACE_NODE)))
    {
        AcpiOsPrintf ("Invalid Named object at address %p\n", Node);
        return;
    }

    AcpiUtDebugDumpBuffer ((void *) Node, sizeof (ACPI_NAMESPACE_NODE),
        Display, ACPI_UINT32_MAX);
    AcpiExDumpNamespaceNode (Node, 1);

    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (ObjDesc)
    {
        AcpiOsPrintf ("\nAttached Object %p:", ObjDesc);
        if (!AcpiOsReadable (ObjDesc, sizeof (ACPI_OPERAND_OBJECT)))
        {
            AcpiOsPrintf ("Invalid internal ACPI Object at address %p\n",
                ObjDesc);
            return;
        }

        if (ACPI_GET_DESCRIPTOR_TYPE (
            ((ACPI_NAMESPACE_NODE *) ObjDesc)) == ACPI_DESC_TYPE_NAMED)
        {
            AcpiOsPrintf (" Namespace Node - ");
            Status = AcpiGetName ((ACPI_NAMESPACE_NODE *) ObjDesc,
                ACPI_FULL_PATHNAME_NO_TRAILING, &RetBuf);
            if (ACPI_FAILURE (Status))
            {
                AcpiOsPrintf ("Could not convert name to pathname\n");
            }
            else
            {
                AcpiOsPrintf ("Pathname: %s",
                    (char *) RetBuf.Pointer);
            }

            AcpiOsPrintf ("\n");
            AcpiUtDebugDumpBuffer ((void *) ObjDesc,
                sizeof (ACPI_NAMESPACE_NODE), Display, ACPI_UINT32_MAX);
        }
        else
        {
            AcpiOsPrintf ("\n");
            AcpiUtDebugDumpBuffer ((void *) ObjDesc,
                sizeof (ACPI_OPERAND_OBJECT), Display, ACPI_UINT32_MAX);
        }

        AcpiExDumpObjectDescriptor (ObjDesc, 1);
    }
}