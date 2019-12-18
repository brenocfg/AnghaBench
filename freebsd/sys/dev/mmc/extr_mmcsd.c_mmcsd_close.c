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
struct mmcsd_softc {int /*<<< orphan*/  dev; } ;
struct mmcsd_part {struct mmcsd_softc* sc; } ;
struct disk {int d_flags; scalar_t__ d_drv1; } ;

/* Variables and functions */
 int DISKFLAG_OPEN ; 
 scalar_t__ MMC_ERR_NONE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mmcsd_flush_cache (struct mmcsd_softc*) ; 

__attribute__((used)) static int
mmcsd_close(struct disk *dp)
{
	struct mmcsd_softc *sc;

	if ((dp->d_flags & DISKFLAG_OPEN) != 0) {
		sc = ((struct mmcsd_part *)dp->d_drv1)->sc;
		if (mmcsd_flush_cache(sc) != MMC_ERR_NONE)
			device_printf(sc->dev, "failed to flush cache\n");
	}
	return (0);
}