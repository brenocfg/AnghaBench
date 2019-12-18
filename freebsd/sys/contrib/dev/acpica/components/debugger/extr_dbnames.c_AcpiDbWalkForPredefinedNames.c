#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_10__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_14__ {TYPE_1__ Name; } ;
struct TYPE_12__ {int /*<<< orphan*/  Count1; int /*<<< orphan*/  ObjectType1; int /*<<< orphan*/  Type; } ;
struct TYPE_11__ {int ExpectedBtypes; int /*<<< orphan*/  ArgumentList; } ;
struct TYPE_13__ {TYPE_3__ RetInfo; TYPE_2__ Info; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int ACPI_RTYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsCheckAcpiCompliance (char*,TYPE_5__*,TYPE_4__ const*) ; 
 char* AcpiNsGetNormalizedPathname (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiUtGetExpectedReturnTypes (char*,int) ; 
 TYPE_4__* AcpiUtMatchPredefinedMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  METHOD_GET_ARG_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbWalkForPredefinedNames (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_NAMESPACE_NODE         *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    UINT32                      *Count = (UINT32 *) Context;
    const ACPI_PREDEFINED_INFO  *Predefined;
    const ACPI_PREDEFINED_INFO  *Package = NULL;
    char                        *Pathname;
    char                        StringBuffer[48];


    Predefined = AcpiUtMatchPredefinedMethod (Node->Name.Ascii);
    if (!Predefined)
    {
        return (AE_OK);
    }

    Pathname = AcpiNsGetNormalizedPathname (Node, TRUE);
    if (!Pathname)
    {
        return (AE_OK);
    }

    /* If method returns a package, the info is in the next table entry */

    if (Predefined->Info.ExpectedBtypes & ACPI_RTYPE_PACKAGE)
    {
        Package = Predefined + 1;
    }

    AcpiUtGetExpectedReturnTypes (StringBuffer,
        Predefined->Info.ExpectedBtypes);

    AcpiOsPrintf ("%-32s Arguments %X, Return Types: %s", Pathname,
        METHOD_GET_ARG_COUNT (Predefined->Info.ArgumentList),
        StringBuffer);

    if (Package)
    {
        AcpiOsPrintf (" (PkgType %2.2X, ObjType %2.2X, Count %2.2X)",
            Package->RetInfo.Type, Package->RetInfo.ObjectType1,
            Package->RetInfo.Count1);
    }

    AcpiOsPrintf("\n");

    /* Check that the declared argument count matches the ACPI spec */

    AcpiNsCheckAcpiCompliance (Pathname, Node, Predefined);

    ACPI_FREE (Pathname);
    (*Count)++;
    return (AE_OK);
}