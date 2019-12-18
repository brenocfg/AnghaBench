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
struct vtblk_softc {int /*<<< orphan*/  vtblk_dev; struct disk* vtblk_disk; } ;
struct disk {int d_sectorsize; scalar_t__ d_mediasize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_VERSION ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  disk_create (struct disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_ident (struct vtblk_softc*) ; 

__attribute__((used)) static void
vtblk_create_disk(struct vtblk_softc *sc)
{
	struct disk *dp;

	dp = sc->vtblk_disk;

	vtblk_ident(sc);

	device_printf(sc->vtblk_dev, "%juMB (%ju %u byte sectors)\n",
	    (uintmax_t) dp->d_mediasize >> 20,
	    (uintmax_t) dp->d_mediasize / dp->d_sectorsize,
	    dp->d_sectorsize);

	disk_create(dp, DISK_VERSION);
}