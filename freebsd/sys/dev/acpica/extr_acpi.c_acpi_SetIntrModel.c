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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 

ACPI_STATUS
acpi_SetIntrModel(int model)
{

    return (acpi_SetInteger(ACPI_ROOT_OBJECT, "_PIC", model));
}