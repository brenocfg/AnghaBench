#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_5__ {char* String; } ;
struct TYPE_6__ {size_t AmlLength; TYPE_1__ Value; } ;
struct TYPE_7__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
UtNameContainsAllPrefix (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Length = Op->Asl.AmlLength;
    UINT32                  i;

    for (i = 0; i < Length; i++)
    {
        if (Op->Asl.Value.String[i] != '^')
        {
            return (FALSE);
        }
    }

    return (TRUE);
}