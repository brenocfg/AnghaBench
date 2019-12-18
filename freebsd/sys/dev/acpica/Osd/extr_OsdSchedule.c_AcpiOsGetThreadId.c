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
struct TYPE_2__ {int /*<<< orphan*/  td_tid; } ;
typedef  int /*<<< orphan*/  ACPI_THREAD_ID ;

/* Variables and functions */
 TYPE_1__* curthread ; 

ACPI_THREAD_ID
AcpiOsGetThreadId(void)
{

    /* XXX do not add ACPI_FUNCTION_TRACE here, results in recursive call. */

    /* Returning 0 is not allowed. */
    return (curthread->td_tid);
}