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
struct TYPE_4__ {int /*<<< orphan*/  ExternalName; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

BOOLEAN
AnIsInternalMethod (
    ACPI_PARSE_OBJECT       *Op)
{

    if ((!strcmp (Op->Asl.ExternalName, "\\_OSI")) ||
        (!strcmp (Op->Asl.ExternalName, "_OSI")))
    {
        return (TRUE);
    }

    return (FALSE);
}