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
struct acpi_cpu_softc {int cpu_disable_idle; } ;

/* Variables and functions */

__attribute__((used)) static int
is_idle_disabled(struct acpi_cpu_softc *sc)
{

    return (sc->cpu_disable_idle);
}