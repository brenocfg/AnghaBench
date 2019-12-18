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
typedef  int uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct vtblk_softc {struct disk* vtblk_disk; int /*<<< orphan*/  vtblk_dev; } ;
struct disk {int d_sectorsize; scalar_t__ d_mediasize; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int disk_resize (struct disk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtblk_resize_disk(struct vtblk_softc *sc, uint64_t new_capacity)
{
	device_t dev;
	struct disk *dp;
	int error;

	dev = sc->vtblk_dev;
	dp = sc->vtblk_disk;

	dp->d_mediasize = new_capacity;
	if (bootverbose) {
		device_printf(dev, "resized to %juMB (%ju %u byte sectors)\n",
		    (uintmax_t) dp->d_mediasize >> 20,
		    (uintmax_t) dp->d_mediasize / dp->d_sectorsize,
		    dp->d_sectorsize);
	}

	error = disk_resize(dp, M_NOWAIT);
	if (error) {
		device_printf(dev,
		    "disk_resize(9) failed, error: %d\n", error);
	}
}