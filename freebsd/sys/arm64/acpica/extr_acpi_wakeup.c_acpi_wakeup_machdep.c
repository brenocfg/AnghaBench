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
struct acpi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

int
acpi_wakeup_machdep(struct acpi_softc *sc, int state, int sleep_result,
    int intr_enabled)
{

	/* ARM64TODO: We will need this with acpi_sleep_machdep */
	KASSERT(sleep_result == -1,
	    ("acpi_wakeup_machdep: Invalid sleep result"));

	return (sleep_result);
}