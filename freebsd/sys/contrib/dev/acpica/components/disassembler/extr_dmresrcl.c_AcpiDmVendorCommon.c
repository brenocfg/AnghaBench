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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmDescriptorName () ; 
 int /*<<< orphan*/  AcpiDmDisasmByteList (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  AcpiDmIndent (scalar_t__) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmVendorCommon (
    const char              *Name,
    UINT8                   *ByteData,
    UINT32                  Length,
    UINT32                  Level)
{

    /* Dump macro name */

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Vendor%s (", Name);

    /* Insert a descriptor name */

    AcpiDmDescriptorName ();
    AcpiOsPrintf (")      // Length = 0x%.2X\n", Length);

    /* Dump the vendor bytes */

    AcpiDmIndent (Level);
    AcpiOsPrintf ("{\n");

    AcpiDmDisasmByteList (Level + 1, ByteData, Length);

    AcpiDmIndent (Level);
    AcpiOsPrintf ("}\n");
}