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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int INT32_MAX ; 
 int N ; 
 scalar_t__ VM_GUEST_NO ; 
 int acpi_TimerDelta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_timer_read () ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ vm_guest ; 

__attribute__((used)) static int
acpi_timer_test()
{
    uint32_t last, this;
    int delta, max, max2, min, n;
    register_t s;

    min = INT32_MAX;
    max = max2 = 0;

    /* Test the timer with interrupts disabled to get accurate results. */
    s = intr_disable();
    last = acpi_timer_read();
    for (n = 0; n < N; n++) {
	this = acpi_timer_read();
	delta = acpi_TimerDelta(this, last);
	if (delta > max) {
	    max2 = max;
	    max = delta;
	} else if (delta > max2)
	    max2 = delta;
	if (delta < min)
	    min = delta;
	last = this;
    }
    intr_restore(s);

    delta = max2 - min;
    if ((max - min > 8 || delta > 3) && vm_guest == VM_GUEST_NO)
	n = 0;
    else if (min < 0 || max == 0 || max2 == 0)
	n = 0;
    else
	n = 1;
    if (bootverbose)
	printf(" %d/%d", n, delta);

    return (n);
}