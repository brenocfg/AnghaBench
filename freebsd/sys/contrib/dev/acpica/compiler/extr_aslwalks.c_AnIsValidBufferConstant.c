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
struct TYPE_4__ {scalar_t__ ParseOpcode; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARSEOP_INTEGER ; 
 scalar_t__ PARSEOP_ONE ; 
 scalar_t__ PARSEOP_ZERO ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AnIsValidBufferConstant (
    ACPI_PARSE_OBJECT       *Op)
{
    if (!Op)
    {
        return (FALSE);
    }

    if ((Op->Asl.ParseOpcode == PARSEOP_INTEGER) ||
        (Op->Asl.ParseOpcode == PARSEOP_ZERO)    ||
        (Op->Asl.ParseOpcode == PARSEOP_ONE))
    {
        return (TRUE);
    }

    return (FALSE);
}