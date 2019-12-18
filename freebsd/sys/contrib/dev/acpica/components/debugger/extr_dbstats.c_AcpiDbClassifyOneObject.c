#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/  Opcode; } ;
struct TYPE_6__ {size_t Type; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 size_t ACPI_TYPE_NS_NODE_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDbEnumerateObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * AcpiGbl_NodeTypeCount ; 
 int /*<<< orphan*/  AcpiGbl_NodeTypeCountMisc ; 
 int /*<<< orphan*/  AcpiGbl_NumNodes ; 
 int /*<<< orphan*/ * AcpiNsGetAttachedObject (TYPE_1__*) ; 
 TYPE_2__* AcpiPsGetDepthNext (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ AcpiPsIsNamedOp (int /*<<< orphan*/ ) ; 
 scalar_t__ IsMethod ; 
 size_t NumGrammarElements ; 
 size_t NumMethodElements ; 
 size_t NumNodes ; 
 TYPE_2__* Op ; 
 int /*<<< orphan*/  Root ; 
 size_t SizeOfAcpiObjects ; 
 size_t SizeOfMethodTrees ; 
 size_t SizeOfNodeEntries ; 
 size_t SizeOfParseTree ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbClassifyOneObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    UINT32                  Type;


    AcpiGbl_NumNodes++;

    Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    ObjDesc = AcpiNsGetAttachedObject (Node);

    AcpiDbEnumerateObject (ObjDesc);

    Type = Node->Type;
    if (Type > ACPI_TYPE_NS_NODE_MAX)
    {
        AcpiGbl_NodeTypeCountMisc++;
    }
    else
    {
        AcpiGbl_NodeTypeCount [Type]++;
    }

    return (AE_OK);


#ifdef ACPI_FUTURE_IMPLEMENTATION

    /* TBD: These need to be counted during the initial parsing phase */

    if (AcpiPsIsNamedOp (Op->Opcode))
    {
        NumNodes++;
    }

    if (IsMethod)
    {
        NumMethodElements++;
    }

    NumGrammarElements++;
    Op = AcpiPsGetDepthNext (Root, Op);

    SizeOfParseTree   = (NumGrammarElements - NumMethodElements) *
        (UINT32) sizeof (ACPI_PARSE_OBJECT);
    SizeOfMethodTrees = NumMethodElements * (UINT32) sizeof (ACPI_PARSE_OBJECT);
    SizeOfNodeEntries = NumNodes * (UINT32) sizeof (ACPI_NAMESPACE_NODE);
    SizeOfAcpiObjects = NumNodes * (UINT32) sizeof (ACPI_OPERAND_OBJECT);
#endif
}