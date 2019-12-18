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
struct acpi_tz_softc {int tz_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tz_proc ; 
 int /*<<< orphan*/  thermal ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
acpi_tz_signal(struct acpi_tz_softc *sc, int flags)
{
    ACPI_LOCK(thermal);
    sc->tz_flags |= flags;
    ACPI_UNLOCK(thermal);
    wakeup(&acpi_tz_proc);
}