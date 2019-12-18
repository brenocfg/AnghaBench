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
typedef  int uint32_t ;
struct cam_iosched_softc {int flags; } ;

/* Variables and functions */

int
cam_iosched_has_work_flags(struct cam_iosched_softc *isc, uint32_t flags)
{
	return isc->flags & flags;
}