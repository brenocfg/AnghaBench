#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_8__ {void* Flags; int /*<<< orphan*/ * Parameters; void* RelativePathname; int /*<<< orphan*/  PrefixNode; } ;
struct TYPE_7__ {scalar_t__ DeviceCount; scalar_t__ Num_STA; scalar_t__ Num_INI; TYPE_2__* EvaluateInfo; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  int /*<<< orphan*/  ACPI_EVALUATE_INFO ;
typedef  TYPE_1__ ACPI_DEVICE_WALK_INFO ;

/* Variables and functions */
 TYPE_2__* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 void* ACPI_IGNORE_RETURN_VALUE ; 
 int ACPI_NO_ADDRESS_SPACE_INIT ; 
 int ACPI_NO_DEVICE_INIT ; 
 scalar_t__ ACPI_OSI_WIN_2000 ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvInitializeOpRegions () ; 
 scalar_t__ AcpiGbl_OsiData ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiGbl_TruncateIoAddresses ; 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiNsEvaluate (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiNsFindIniMethods ; 
 int /*<<< orphan*/  AcpiNsInitOneDevice ; 
 int /*<<< orphan*/  AcpiNsWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 void* METHOD_NAME__INI ; 
 int /*<<< orphan*/  NsInitializeDevices ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiNsInitializeDevices (
    UINT32                  Flags)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_DEVICE_WALK_INFO   Info;
    ACPI_HANDLE             Handle;


    ACPI_FUNCTION_TRACE (NsInitializeDevices);


    if (!(Flags & ACPI_NO_DEVICE_INIT))
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "[Init] Initializing ACPI Devices\n"));

        /* Init counters */

        Info.DeviceCount = 0;
        Info.Num_STA = 0;
        Info.Num_INI = 0;

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_INIT,
            "Initializing Device/Processor/Thermal objects "
            "and executing _INI/_STA methods:\n"));

        /* Tree analysis: find all subtrees that contain _INI methods */

        Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
            ACPI_UINT32_MAX, FALSE, AcpiNsFindIniMethods, NULL, &Info, NULL);
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }

        /* Allocate the evaluation information block */

        Info.EvaluateInfo = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_EVALUATE_INFO));
        if (!Info.EvaluateInfo)
        {
            Status = AE_NO_MEMORY;
            goto ErrorExit;
        }

        /*
         * Execute the "global" _INI method that may appear at the root.
         * This support is provided for Windows compatibility (Vista+) and
         * is not part of the ACPI specification.
         */
        Info.EvaluateInfo->PrefixNode = AcpiGbl_RootNode;
        Info.EvaluateInfo->RelativePathname = METHOD_NAME__INI;
        Info.EvaluateInfo->Parameters = NULL;
        Info.EvaluateInfo->Flags = ACPI_IGNORE_RETURN_VALUE;

        Status = AcpiNsEvaluate (Info.EvaluateInfo);
        if (ACPI_SUCCESS (Status))
        {
            Info.Num_INI++;
        }

        /*
         * Execute \_SB._INI.
         * There appears to be a strict order requirement for \_SB._INI,
         * which should be evaluated before any _REG evaluations.
         */
        Status = AcpiGetHandle (NULL, "\\_SB", &Handle);
        if (ACPI_SUCCESS (Status))
        {
            memset (Info.EvaluateInfo, 0, sizeof (ACPI_EVALUATE_INFO));
            Info.EvaluateInfo->PrefixNode = Handle;
            Info.EvaluateInfo->RelativePathname = METHOD_NAME__INI;
            Info.EvaluateInfo->Parameters = NULL;
            Info.EvaluateInfo->Flags = ACPI_IGNORE_RETURN_VALUE;

            Status = AcpiNsEvaluate (Info.EvaluateInfo);
            if (ACPI_SUCCESS (Status))
            {
                Info.Num_INI++;
            }
        }
    }

    /*
     * Run all _REG methods
     *
     * Note: Any objects accessed by the _REG methods will be automatically
     * initialized, even if they contain executable AML (see the call to
     * AcpiNsInitializeObjects below).
     *
     * Note: According to the ACPI specification, we actually needn't execute
     * _REG for SystemMemory/SystemIo operation regions, but for PCI_Config
     * operation regions, it is required to evaluate _REG for those on a PCI
     * root bus that doesn't contain _BBN object. So this code is kept here
     * in order not to break things.
     */
    if (!(Flags & ACPI_NO_ADDRESS_SPACE_INIT))
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "[Init] Executing _REG OpRegion methods\n"));

        Status = AcpiEvInitializeOpRegions ();
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }
    }

    if (!(Flags & ACPI_NO_DEVICE_INIT))
    {
        /* Walk namespace to execute all _INIs on present devices */

        Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
            ACPI_UINT32_MAX, FALSE, AcpiNsInitOneDevice, NULL, &Info, NULL);

        /*
         * Any _OSI requests should be completed by now. If the BIOS has
         * requested any Windows OSI strings, we will always truncate
         * I/O addresses to 16 bits -- for Windows compatibility.
         */
        if (AcpiGbl_OsiData >= ACPI_OSI_WIN_2000)
        {
            AcpiGbl_TruncateIoAddresses = TRUE;
        }

        ACPI_FREE (Info.EvaluateInfo);
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_INIT,
            "    Executed %u _INI methods requiring %u _STA executions "
            "(examined %u objects)\n",
            Info.Num_INI, Info.Num_STA, Info.DeviceCount));
    }

    return_ACPI_STATUS (Status);


ErrorExit:
    ACPI_EXCEPTION ((AE_INFO, Status, "During device initialization"));
    return_ACPI_STATUS (Status);
}