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
typedef  int UINT32 ;
struct TYPE_5__ {int GpeNumber; TYPE_1__* RegisterInfo; } ;
struct TYPE_4__ {int BaseGpeNumber; } ;
typedef  TYPE_2__ ACPI_GPE_EVENT_INFO ;

/* Variables and functions */

UINT32
AcpiHwGetGpeRegisterBit (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo)
{

    return ((UINT32) 1 <<
        (GpeEventInfo->GpeNumber - GpeEventInfo->RegisterInfo->BaseGpeNumber));
}