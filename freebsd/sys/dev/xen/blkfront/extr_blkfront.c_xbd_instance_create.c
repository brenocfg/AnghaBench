#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct xbd_softc {int xbd_unit; int xbd_flags; TYPE_1__* xbd_disk; int /*<<< orphan*/  xbd_dev; int /*<<< orphan*/  xbd_max_request_size; } ;
typedef  int /*<<< orphan*/  features ;
typedef  unsigned long blkif_sector_t ;
struct TYPE_3__ {int d_unit; char const* d_name; unsigned long d_sectorsize; unsigned long d_stripesize; unsigned long d_mediasize; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_maxsize; scalar_t__ d_stripeoffset; struct xbd_softc* d_drv1; int /*<<< orphan*/  d_dump; int /*<<< orphan*/  d_strategy; int /*<<< orphan*/  d_ioctl; int /*<<< orphan*/  d_close; int /*<<< orphan*/  d_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISKFLAG_CANFLUSHCACHE ; 
 int /*<<< orphan*/  DISKFLAG_UNMAPPED_BIO ; 
 int /*<<< orphan*/  DISK_VERSION ; 
 int XBDF_BARRIER ; 
 int XBDF_FLUSH ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xbd_close ; 
 int /*<<< orphan*/  xbd_dump ; 
 scalar_t__ xbd_feature_string (struct xbd_softc*,char*,int) ; 
 int /*<<< orphan*/  xbd_ioctl ; 
 int /*<<< orphan*/  xbd_open ; 
 int /*<<< orphan*/  xbd_strategy ; 
 int /*<<< orphan*/  xbd_vdevice_to_unit (int,int*,char const**) ; 

int
xbd_instance_create(struct xbd_softc *sc, blkif_sector_t sectors,
    int vdevice, uint16_t vdisk_info, unsigned long sector_size,
    unsigned long phys_sector_size)
{
	char features[80];
	int unit, error = 0;
	const char *name;

	xbd_vdevice_to_unit(vdevice, &unit, &name);

	sc->xbd_unit = unit;

	if (strcmp(name, "xbd") != 0)
		device_printf(sc->xbd_dev, "attaching as %s%d\n", name, unit);

	if (xbd_feature_string(sc, features, sizeof(features)) > 0) {
		device_printf(sc->xbd_dev, "features: %s\n",
		    features);
	}

	sc->xbd_disk = disk_alloc();
	sc->xbd_disk->d_unit = sc->xbd_unit;
	sc->xbd_disk->d_open = xbd_open;
	sc->xbd_disk->d_close = xbd_close;
	sc->xbd_disk->d_ioctl = xbd_ioctl;
	sc->xbd_disk->d_strategy = xbd_strategy;
	sc->xbd_disk->d_dump = xbd_dump;
	sc->xbd_disk->d_name = name;
	sc->xbd_disk->d_drv1 = sc;
	sc->xbd_disk->d_sectorsize = sector_size;
	sc->xbd_disk->d_stripesize = phys_sector_size;
	sc->xbd_disk->d_stripeoffset = 0;

	sc->xbd_disk->d_mediasize = sectors * sector_size;
	sc->xbd_disk->d_maxsize = sc->xbd_max_request_size;
	sc->xbd_disk->d_flags = DISKFLAG_UNMAPPED_BIO;
	if ((sc->xbd_flags & (XBDF_FLUSH|XBDF_BARRIER)) != 0) {
		sc->xbd_disk->d_flags |= DISKFLAG_CANFLUSHCACHE;
		device_printf(sc->xbd_dev,
		    "synchronize cache commands enabled.\n");
	}
	disk_create(sc->xbd_disk, DISK_VERSION);

	return error;
}