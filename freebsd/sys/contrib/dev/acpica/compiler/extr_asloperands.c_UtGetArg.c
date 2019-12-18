#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {TYPE_2__* Next; TYPE_2__* Child; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */

ACPI_PARSE_OBJECT *
UtGetArg (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Argn)
{
    ACPI_PARSE_OBJECT       *Arg = NULL;


    /* Get the requested argument object */

    Arg = Op->Asl.Child;
    while (Arg && Argn)
    {
        Argn--;
        Arg = Arg->Asl.Next;
    }

    return (Arg);
}