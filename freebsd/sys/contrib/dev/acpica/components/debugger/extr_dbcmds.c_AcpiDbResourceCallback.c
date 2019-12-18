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
typedef  int /*<<< orphan*/  ACPI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbResourceCallback (
    ACPI_RESOURCE           *Resource,
    void                    *Context)
{

    return (AE_OK);
}