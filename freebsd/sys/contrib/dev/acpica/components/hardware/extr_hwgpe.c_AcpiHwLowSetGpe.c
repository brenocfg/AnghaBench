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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT32 ;
struct TYPE_6__ {TYPE_1__* RegisterInfo; } ;
struct TYPE_5__ {int EnableMask; int MaskForRun; int /*<<< orphan*/  EnableAddress; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_GPE_REGISTER_INFO ;
typedef  TYPE_2__ ACPI_GPE_EVENT_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CLEAR_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
#define  ACPI_GPE_CONDITIONAL_ENABLE 130 
#define  ACPI_GPE_DISABLE 129 
#define  ACPI_GPE_ENABLE 128 
 int /*<<< orphan*/  ACPI_SET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int AcpiHwGetGpeRegisterBit (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiHwRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ACPI_STATUS
AcpiHwLowSetGpe (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo,
    UINT32                  Action)
{
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;
    ACPI_STATUS             Status = AE_OK;
    UINT64                  EnableMask;
    UINT32                  RegisterBit;


    ACPI_FUNCTION_ENTRY ();


    /* Get the info block for the entire GPE register */

    GpeRegisterInfo = GpeEventInfo->RegisterInfo;
    if (!GpeRegisterInfo)
    {
        return (AE_NOT_EXIST);
    }

    /* Get current value of the enable register that contains this GPE */

    Status = AcpiHwRead (&EnableMask, &GpeRegisterInfo->EnableAddress);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Set or clear just the bit that corresponds to this GPE */

    RegisterBit = AcpiHwGetGpeRegisterBit (GpeEventInfo);
    switch (Action)
    {
    case ACPI_GPE_CONDITIONAL_ENABLE:

        /* Only enable if the corresponding EnableMask bit is set */

        if (!(RegisterBit & GpeRegisterInfo->EnableMask))
        {
            return (AE_BAD_PARAMETER);
        }

        /*lint -fallthrough */

    case ACPI_GPE_ENABLE:

        ACPI_SET_BIT (EnableMask, RegisterBit);
        break;

    case ACPI_GPE_DISABLE:

        ACPI_CLEAR_BIT (EnableMask, RegisterBit);
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Invalid GPE Action, %u", Action));
        return (AE_BAD_PARAMETER);
    }

    if (!(RegisterBit & GpeRegisterInfo->MaskForRun))
    {
        /* Write the updated enable mask */

        Status = AcpiHwWrite (EnableMask, &GpeRegisterInfo->EnableAddress);
    }
    return (Status);
}