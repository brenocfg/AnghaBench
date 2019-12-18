#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
struct aac_softc {int flags; int aac_max_sectors; } ;
struct aac_disk {int ad_size; int ad_heads; int ad_sectors; int ad_cylinders; TYPE_2__* ad_disk; int /*<<< orphan*/  unit; struct aac_softc* ad_controller; TYPE_4__* ad_container; int /*<<< orphan*/  ad_dev; } ;
typedef  int off_t ;
typedef  int intmax_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int Capacity; scalar_t__ CapacityHigh; } ;
struct TYPE_7__ {TYPE_1__ co_mntobj; } ;
struct TYPE_6__ {char* d_name; int d_maxsize; int d_sectorsize; int d_mediasize; int d_fwsectors; int d_fwheads; int /*<<< orphan*/  d_unit; int /*<<< orphan*/  d_dump; int /*<<< orphan*/  d_strategy; int /*<<< orphan*/  d_close; int /*<<< orphan*/  d_open; int /*<<< orphan*/  d_flags; struct aac_disk* d_drv1; } ;

/* Variables and functions */
 int AAC_BLOCK_SIZE ; 
 int AAC_FLAGS_LBA_64BIT ; 
 int /*<<< orphan*/  DISKFLAG_UNMAPPED_BIO ; 
 int /*<<< orphan*/  DISK_VERSION ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  aac_disk_close ; 
 int /*<<< orphan*/  aac_disk_dump ; 
 int /*<<< orphan*/  aac_disk_open ; 
 int /*<<< orphan*/  aac_disk_strategy ; 
 TYPE_4__* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_2__* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
aac_disk_attach(device_t dev)
{
	struct aac_disk	*sc;
	
	sc = (struct aac_disk *)device_get_softc(dev);
	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* initialise our softc */
	sc->ad_controller =
	    (struct aac_softc *)device_get_softc(device_get_parent(dev));
	sc->ad_container = device_get_ivars(dev);
	sc->ad_dev = dev;

	/*
	 * require that extended translation be enabled - other drivers read the
	 * disk!
	 */
	sc->ad_size = sc->ad_container->co_mntobj.Capacity;
	if (sc->ad_controller->flags & AAC_FLAGS_LBA_64BIT)
		sc->ad_size += (u_int64_t)
			sc->ad_container->co_mntobj.CapacityHigh << 32;
	if (sc->ad_size >= (2 * 1024 * 1024)) {		/* 2GB */
		sc->ad_heads = 255;
		sc->ad_sectors = 63;
	} else if (sc->ad_size >= (1 * 1024 * 1024)) {	/* 1GB */
		sc->ad_heads = 128;
		sc->ad_sectors = 32;
	} else {
		sc->ad_heads = 64;
		sc->ad_sectors = 32;
	}
	sc->ad_cylinders = (sc->ad_size / (sc->ad_heads * sc->ad_sectors));

	device_printf(dev, "%juMB (%ju sectors)\n",
		      (intmax_t)sc->ad_size / ((1024 * 1024) / AAC_BLOCK_SIZE),
		      (intmax_t)sc->ad_size);

	/* attach a generic disk device to ourselves */
	sc->unit = device_get_unit(dev);
	sc->ad_disk = disk_alloc();
	sc->ad_disk->d_drv1 = sc;
	sc->ad_disk->d_flags = DISKFLAG_UNMAPPED_BIO;
	sc->ad_disk->d_name = "aacd";
	sc->ad_disk->d_maxsize = sc->ad_controller->aac_max_sectors << 9;
	sc->ad_disk->d_open = aac_disk_open;
	sc->ad_disk->d_close = aac_disk_close;
	sc->ad_disk->d_strategy = aac_disk_strategy;
	sc->ad_disk->d_dump = aac_disk_dump;
	sc->ad_disk->d_sectorsize = AAC_BLOCK_SIZE;
	sc->ad_disk->d_mediasize = (off_t)sc->ad_size * AAC_BLOCK_SIZE;
	sc->ad_disk->d_fwsectors = sc->ad_sectors;
	sc->ad_disk->d_fwheads = sc->ad_heads;
	sc->ad_disk->d_unit = sc->unit;
	disk_create(sc->ad_disk, DISK_VERSION);

	return (0);
}