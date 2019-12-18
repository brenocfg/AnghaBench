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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

void
AslDisassemblyHelp (
    void)
{

    printf ("\nObtaining binary ACPI tables and disassembling to ASL source code.\n\n");
    printf ("Use the following ACPICA toolchain:\n");
    printf ("  AcpiDump: Dump all ACPI tables to a hex ascii file\n");
    printf ("  AcpiXtract: Extract one or more binary ACPI tables from AcpiDump output\n");
    printf ("  iASL -d <file>: Disassemble a binary ACPI table to ASL source code\n");
    printf ("\n");
}