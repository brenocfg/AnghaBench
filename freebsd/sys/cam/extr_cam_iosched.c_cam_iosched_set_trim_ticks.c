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
struct cam_iosched_softc {int trim_ticks; } ;

/* Variables and functions */

void
cam_iosched_set_trim_ticks(struct cam_iosched_softc *isc, int trim_ticks)
{

	isc->trim_ticks = trim_ticks;
}