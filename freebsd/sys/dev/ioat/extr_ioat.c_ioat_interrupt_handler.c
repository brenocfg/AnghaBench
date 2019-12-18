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
struct TYPE_2__ {int /*<<< orphan*/  interrupts; } ;
struct ioat_softc {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ioat_process_events (struct ioat_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ioat_interrupt_handler(void *arg)
{
	struct ioat_softc *ioat = arg;

	ioat->stats.interrupts++;
	ioat_process_events(ioat, TRUE);
}