#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * ASL_GET_PEER_NODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT16
RsGetInterruptDataLength (
    ACPI_PARSE_OBJECT       *InitializerOp,
    UINT32                  StartIndex)
{
    UINT16                  InterruptLength;
    UINT32                  i;


    /* Count the interrupt numbers */

    InterruptLength = 0;
    for (i = 0; InitializerOp; i++)
    {
        InitializerOp = ASL_GET_PEER_NODE (InitializerOp);

        /* Interrupt list starts at offset StartIndex (Gpio descriptors) */

        if (i >= StartIndex)
        {
            InterruptLength += 2;
        }
    }

    return (InterruptLength);
}