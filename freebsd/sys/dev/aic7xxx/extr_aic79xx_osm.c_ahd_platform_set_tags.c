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
struct ahd_softc {int dummy; } ;
struct ahd_devinfo {int dummy; } ;

/* Variables and functions */

void
ahd_platform_set_tags(struct ahd_softc *ahd,
		      struct ahd_devinfo *devinfo, int enable)
{
}