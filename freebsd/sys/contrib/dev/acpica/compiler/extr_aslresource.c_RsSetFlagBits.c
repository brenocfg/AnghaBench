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
typedef  int UINT8 ;
struct TYPE_5__ {scalar_t__ Integer; } ;
struct TYPE_6__ {scalar_t__ ParseOpcode; TYPE_1__ Value; } ;
struct TYPE_7__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ PARSEOP_DEFAULT_ARG ; 

void
RsSetFlagBits (
    UINT8                   *Flags,
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   Position,
    UINT8                   DefaultBit)
{

    if (Op->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)
    {
        /* Use the default bit */

        *Flags |= (DefaultBit << Position);
    }
    else
    {
        /* Use the bit specified in the initialization node */

        *Flags |= (((UINT8) Op->Asl.Value.Integer) << Position);
    }
}