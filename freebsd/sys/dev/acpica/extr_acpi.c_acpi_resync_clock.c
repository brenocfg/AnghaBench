#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acpi_softc {scalar_t__ acpi_sleep_delay; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tc_get_timecount ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  inittodr (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 scalar_t__ time_second ; 
 TYPE_1__* timecounter ; 

__attribute__((used)) static void
acpi_resync_clock(struct acpi_softc *sc)
{

    /*
     * Warm up timecounter again and reset system clock.
     */
    (void)timecounter->tc_get_timecount(timecounter);
    (void)timecounter->tc_get_timecount(timecounter);
    inittodr(time_second + sc->acpi_sleep_delay);
}