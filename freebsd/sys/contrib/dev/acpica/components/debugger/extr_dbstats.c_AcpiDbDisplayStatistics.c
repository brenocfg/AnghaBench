#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  UseCount; } ;
typedef  int /*<<< orphan*/  ACPI_UPDATE_STATE ;
typedef  int /*<<< orphan*/  ACPI_THREAD_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SCOPE_STATE ;
typedef  int /*<<< orphan*/  ACPI_RESULT_VALUES ;
typedef  int /*<<< orphan*/  ACPI_PSCOPE_STATE ;
typedef  int /*<<< orphan*/  ACPI_PKG_STATE ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJ_NAMED ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJ_COMMON ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJ_ASL ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_THERMAL_ZONE ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_STRING ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_REGION_FIELD ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_REGION ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_REFERENCE ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_PROCESSOR ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_POWER_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_PACKAGE ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_NOTIFY_HANDLER ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_MUTEX ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_METHOD ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_INTEGER ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_INDEX_FIELD ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_EXTRA ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_EVENT ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_DEVICE ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_DATA ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_COMMON ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_BUFFER_FIELD ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_BUFFER ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_BANK_FIELD ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_ADDR_HANDLER ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NOTIFY_INFO ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  int /*<<< orphan*/  ACPI_GENERIC_STATE ;
typedef  int /*<<< orphan*/  ACPI_CONTROL_STATE ;
typedef  int /*<<< orphan*/  ACPI_COMMON_STATE ;

/* Variables and functions */
 int ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ACPI_TYPE_NOT_FOUND ; 
 int ACPI_TYPE_NS_NODE_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDbCountNamespaceObjects () ; 
 int /*<<< orphan*/  AcpiDbListInfo (int /*<<< orphan*/ ) ; 
 int AcpiDbMatchArgument (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDbStatTypes ; 
 int /*<<< orphan*/  AcpiGbl_DeepestNesting ; 
 int /*<<< orphan*/  AcpiGbl_EntryStackPointer ; 
 int /*<<< orphan*/  AcpiGbl_GlobalList ; 
 int /*<<< orphan*/  AcpiGbl_LowestStackPointer ; 
 TYPE_1__* AcpiGbl_MutexInfo ; 
 int /*<<< orphan*/ * AcpiGbl_NodeTypeCount ; 
 int /*<<< orphan*/  AcpiGbl_NodeTypeCountMisc ; 
 int /*<<< orphan*/  AcpiGbl_NsLookupCount ; 
 int /*<<< orphan*/  AcpiGbl_NsNodeList ; 
 int /*<<< orphan*/  AcpiGbl_NumNodes ; 
 int /*<<< orphan*/  AcpiGbl_NumObjects ; 
 int /*<<< orphan*/ * AcpiGbl_ObjTypeCount ; 
 int /*<<< orphan*/  AcpiGbl_ObjTypeCountMisc ; 
 int /*<<< orphan*/  AcpiGbl_OperandCache ; 
 int /*<<< orphan*/  AcpiGbl_PsFindCount ; 
 int /*<<< orphan*/  AcpiGbl_PsNodeCache ; 
 int /*<<< orphan*/  AcpiGbl_PsNodeExtCache ; 
 int /*<<< orphan*/  AcpiGbl_StateCache ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiUtDumpAllocationInfo () ; 
 int /*<<< orphan*/  AcpiUtGetMutexName (int) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int) ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
#define  CMD_STAT_ALLOCATIONS 134 
#define  CMD_STAT_MEMORY 133 
#define  CMD_STAT_MISC 132 
#define  CMD_STAT_OBJECTS 131 
#define  CMD_STAT_SIZES 130 
#define  CMD_STAT_STACK 129 
#define  CMD_STAT_TABLES 128 

ACPI_STATUS
AcpiDbDisplayStatistics (
    char                    *TypeArg)
{
    UINT32                  i;
    UINT32                  Temp;


    AcpiUtStrupr (TypeArg);
    Temp = AcpiDbMatchArgument (TypeArg, AcpiDbStatTypes);
    if (Temp == ACPI_TYPE_NOT_FOUND)
    {
        AcpiOsPrintf ("Invalid or unsupported argument\n");
        return (AE_OK);
    }


    switch (Temp)
    {
    case CMD_STAT_ALLOCATIONS:

#ifdef ACPI_DBG_TRACK_ALLOCATIONS
        AcpiUtDumpAllocationInfo ();
#endif
        break;

    case CMD_STAT_TABLES:

        AcpiOsPrintf ("ACPI Table Information (not implemented):\n\n");
        break;

    case CMD_STAT_OBJECTS:

        AcpiDbCountNamespaceObjects ();

        AcpiOsPrintf ("\nObjects defined in the current namespace:\n\n");

        AcpiOsPrintf ("%16.16s %10.10s %10.10s\n",
            "ACPI_TYPE", "NODES", "OBJECTS");

        for (i = 0; i < ACPI_TYPE_NS_NODE_MAX; i++)
        {
            AcpiOsPrintf ("%16.16s %10u %10u\n", AcpiUtGetTypeName (i),
                AcpiGbl_NodeTypeCount [i], AcpiGbl_ObjTypeCount [i]);
        }

        AcpiOsPrintf ("%16.16s %10u %10u\n", "Misc/Unknown",
            AcpiGbl_NodeTypeCountMisc, AcpiGbl_ObjTypeCountMisc);

        AcpiOsPrintf ("%16.16s %10u %10u\n", "TOTALS:",
            AcpiGbl_NumNodes, AcpiGbl_NumObjects);
        break;

    case CMD_STAT_MEMORY:

#ifdef ACPI_DBG_TRACK_ALLOCATIONS
        AcpiOsPrintf ("\n----Object Statistics (all in hex)---------\n");

        AcpiDbListInfo (AcpiGbl_GlobalList);
        AcpiDbListInfo (AcpiGbl_NsNodeList);
#endif

#ifdef ACPI_USE_LOCAL_CACHE
        AcpiOsPrintf ("\n----Cache Statistics (all in hex)---------\n");
        AcpiDbListInfo (AcpiGbl_OperandCache);
        AcpiDbListInfo (AcpiGbl_PsNodeCache);
        AcpiDbListInfo (AcpiGbl_PsNodeExtCache);
        AcpiDbListInfo (AcpiGbl_StateCache);
#endif

        break;

    case CMD_STAT_MISC:

        AcpiOsPrintf ("\nMiscellaneous Statistics:\n\n");
        AcpiOsPrintf ("%-28s:       %7u\n", "Calls to AcpiPsFind",
            AcpiGbl_PsFindCount);
        AcpiOsPrintf ("%-28s:       %7u\n", "Calls to AcpiNsLookup",
            AcpiGbl_NsLookupCount);

        AcpiOsPrintf ("\nMutex usage:\n\n");
        for (i = 0; i < ACPI_NUM_MUTEX; i++)
        {
            AcpiOsPrintf ("%-28s:       %7u\n",
                AcpiUtGetMutexName (i), AcpiGbl_MutexInfo[i].UseCount);
        }
        break;

    case CMD_STAT_SIZES:

        AcpiOsPrintf ("\nInternal object sizes:\n\n");

        AcpiOsPrintf ("Common           %3d\n", (UINT32) sizeof (ACPI_OBJECT_COMMON));
        AcpiOsPrintf ("Number           %3d\n", (UINT32) sizeof (ACPI_OBJECT_INTEGER));
        AcpiOsPrintf ("String           %3d\n", (UINT32) sizeof (ACPI_OBJECT_STRING));
        AcpiOsPrintf ("Buffer           %3d\n", (UINT32) sizeof (ACPI_OBJECT_BUFFER));
        AcpiOsPrintf ("Package          %3d\n", (UINT32) sizeof (ACPI_OBJECT_PACKAGE));
        AcpiOsPrintf ("BufferField      %3d\n", (UINT32) sizeof (ACPI_OBJECT_BUFFER_FIELD));
        AcpiOsPrintf ("Device           %3d\n", (UINT32) sizeof (ACPI_OBJECT_DEVICE));
        AcpiOsPrintf ("Event            %3d\n", (UINT32) sizeof (ACPI_OBJECT_EVENT));
        AcpiOsPrintf ("Method           %3d\n", (UINT32) sizeof (ACPI_OBJECT_METHOD));
        AcpiOsPrintf ("Mutex            %3d\n", (UINT32) sizeof (ACPI_OBJECT_MUTEX));
        AcpiOsPrintf ("Region           %3d\n", (UINT32) sizeof (ACPI_OBJECT_REGION));
        AcpiOsPrintf ("PowerResource    %3d\n", (UINT32) sizeof (ACPI_OBJECT_POWER_RESOURCE));
        AcpiOsPrintf ("Processor        %3d\n", (UINT32) sizeof (ACPI_OBJECT_PROCESSOR));
        AcpiOsPrintf ("ThermalZone      %3d\n", (UINT32) sizeof (ACPI_OBJECT_THERMAL_ZONE));
        AcpiOsPrintf ("RegionField      %3d\n", (UINT32) sizeof (ACPI_OBJECT_REGION_FIELD));
        AcpiOsPrintf ("BankField        %3d\n", (UINT32) sizeof (ACPI_OBJECT_BANK_FIELD));
        AcpiOsPrintf ("IndexField       %3d\n", (UINT32) sizeof (ACPI_OBJECT_INDEX_FIELD));
        AcpiOsPrintf ("Reference        %3d\n", (UINT32) sizeof (ACPI_OBJECT_REFERENCE));
        AcpiOsPrintf ("Notify           %3d\n", (UINT32) sizeof (ACPI_OBJECT_NOTIFY_HANDLER));
        AcpiOsPrintf ("AddressSpace     %3d\n", (UINT32) sizeof (ACPI_OBJECT_ADDR_HANDLER));
        AcpiOsPrintf ("Extra            %3d\n", (UINT32) sizeof (ACPI_OBJECT_EXTRA));
        AcpiOsPrintf ("Data             %3d\n", (UINT32) sizeof (ACPI_OBJECT_DATA));

        AcpiOsPrintf ("\n");

        AcpiOsPrintf ("ParseObject      %3d\n", (UINT32) sizeof (ACPI_PARSE_OBJ_COMMON));
        AcpiOsPrintf ("ParseObjectNamed %3d\n", (UINT32) sizeof (ACPI_PARSE_OBJ_NAMED));
        AcpiOsPrintf ("ParseObjectAsl   %3d\n", (UINT32) sizeof (ACPI_PARSE_OBJ_ASL));
        AcpiOsPrintf ("OperandObject    %3d\n", (UINT32) sizeof (ACPI_OPERAND_OBJECT));
        AcpiOsPrintf ("NamespaceNode    %3d\n", (UINT32) sizeof (ACPI_NAMESPACE_NODE));
        AcpiOsPrintf ("AcpiObject       %3d\n", (UINT32) sizeof (ACPI_OBJECT));

        AcpiOsPrintf ("\n");

        AcpiOsPrintf ("Generic State    %3d\n", (UINT32) sizeof (ACPI_GENERIC_STATE));
        AcpiOsPrintf ("Common State     %3d\n", (UINT32) sizeof (ACPI_COMMON_STATE));
        AcpiOsPrintf ("Control State    %3d\n", (UINT32) sizeof (ACPI_CONTROL_STATE));
        AcpiOsPrintf ("Update State     %3d\n", (UINT32) sizeof (ACPI_UPDATE_STATE));
        AcpiOsPrintf ("Scope State      %3d\n", (UINT32) sizeof (ACPI_SCOPE_STATE));
        AcpiOsPrintf ("Parse Scope      %3d\n", (UINT32) sizeof (ACPI_PSCOPE_STATE));
        AcpiOsPrintf ("Package State    %3d\n", (UINT32) sizeof (ACPI_PKG_STATE));
        AcpiOsPrintf ("Thread State     %3d\n", (UINT32) sizeof (ACPI_THREAD_STATE));
        AcpiOsPrintf ("Result Values    %3d\n", (UINT32) sizeof (ACPI_RESULT_VALUES));
        AcpiOsPrintf ("Notify Info      %3d\n", (UINT32) sizeof (ACPI_NOTIFY_INFO));
        break;

    case CMD_STAT_STACK:
#if defined(ACPI_DEBUG_OUTPUT)

        Temp = (UINT32) ACPI_PTR_DIFF (
            AcpiGbl_EntryStackPointer, AcpiGbl_LowestStackPointer);

        AcpiOsPrintf ("\nSubsystem Stack Usage:\n\n");
        AcpiOsPrintf ("Entry Stack Pointer          %p\n", AcpiGbl_EntryStackPointer);
        AcpiOsPrintf ("Lowest Stack Pointer         %p\n", AcpiGbl_LowestStackPointer);
        AcpiOsPrintf ("Stack Use                    %X (%u)\n", Temp, Temp);
        AcpiOsPrintf ("Deepest Procedure Nesting    %u\n", AcpiGbl_DeepestNesting);
#endif
        break;

    default:

        break;
    }

    AcpiOsPrintf ("\n");
    return (AE_OK);
}