#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  ExternalName; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BTYPE_STRING ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

UINT32
AnGetInternalMethodReturnType (
    ACPI_PARSE_OBJECT       *Op)
{

    if ((!strcmp (Op->Asl.ExternalName, "\\_OSI")) ||
        (!strcmp (Op->Asl.ExternalName, "_OSI")))
    {
        return (ACPI_BTYPE_STRING);
    }

    return (0);
}