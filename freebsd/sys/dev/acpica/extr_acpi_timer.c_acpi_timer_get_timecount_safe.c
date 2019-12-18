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
typedef  scalar_t__ u_int ;
struct timecounter {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_timer_read () ; 

__attribute__((used)) static u_int
acpi_timer_get_timecount_safe(struct timecounter *tc)
{
    u_int u1, u2, u3;

    u2 = acpi_timer_read();
    u3 = acpi_timer_read();
    do {
	u1 = u2;
	u2 = u3;
	u3 = acpi_timer_read();
    } while (u1 > u2 || u2 > u3);

    return (u2);
}