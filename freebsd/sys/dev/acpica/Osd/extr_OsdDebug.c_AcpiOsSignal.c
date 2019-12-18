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
struct TYPE_2__ {int Type; int Code; int Argument; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_SIGNAL_FATAL_INFO ;

/* Variables and functions */
#define  ACPI_SIGNAL_BREAKPOINT 129 
#define  ACPI_SIGNAL_FATAL 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  KDB_WHY_ACPI ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

ACPI_STATUS
AcpiOsSignal(UINT32 Function, void *Info)
{
    ACPI_SIGNAL_FATAL_INFO	*fatal;

    switch (Function) {
    case ACPI_SIGNAL_FATAL:
	fatal = (ACPI_SIGNAL_FATAL_INFO *)Info;
	printf("ACPI fatal signal, type 0x%x code 0x%x argument 0x%x",
	      fatal->Type, fatal->Code, fatal->Argument);
#ifdef ACPI_DEBUG
	kdb_enter(KDB_WHY_ACPI, "AcpiOsSignal");
#endif
	break;

    case ACPI_SIGNAL_BREAKPOINT:
#ifdef ACPI_DEBUG
	kdb_enter(KDB_WHY_ACPI, (char *)Info);
#endif
	break;

    default:
	return (AE_BAD_PARAMETER);
    }

    return (AE_OK);
}