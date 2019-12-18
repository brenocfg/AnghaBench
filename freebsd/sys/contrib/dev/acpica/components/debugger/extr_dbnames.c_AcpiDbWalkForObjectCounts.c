#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_6__ {size_t Type; TYPE_1__ Name; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Types; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT_INFO ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 size_t ACPI_TYPE_NS_NODE_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbWalkForObjectCounts (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OBJECT_INFO        *Info = (ACPI_OBJECT_INFO *) Context;
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;


    if (Node->Type > ACPI_TYPE_NS_NODE_MAX)
    {
        AcpiOsPrintf ("[%4.4s]: Unknown object type %X\n",
            Node->Name.Ascii, Node->Type);
    }
    else
    {
        Info->Types[Node->Type]++;
    }

    return (AE_OK);
}