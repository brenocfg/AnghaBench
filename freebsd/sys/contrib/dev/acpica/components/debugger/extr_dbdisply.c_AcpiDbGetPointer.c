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
typedef  int /*<<< orphan*/  ACPI_SIZE ;

/* Variables and functions */
 void* ACPI_TO_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *
AcpiDbGetPointer (
    void                    *Target)
{
    void                    *ObjPtr;
    ACPI_SIZE               Address;


    Address = strtoul (Target, NULL, 16);
    ObjPtr = ACPI_TO_POINTER (Address);
    return (ObjPtr);
}