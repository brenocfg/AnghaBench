#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct idad_softc {intptr_t drive; int secsize; int secperunit; TYPE_2__* disk; int /*<<< orphan*/  unit; int /*<<< orphan*/  heads; int /*<<< orphan*/  sectors; int /*<<< orphan*/  cylinders; struct ida_softc* controller; int /*<<< orphan*/  dev; } ;
struct ida_softc {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  nsectors; int /*<<< orphan*/  nheads; int /*<<< orphan*/  ncylinders; } ;
struct ida_drive_info {int secsize; int secperunit; TYPE_1__ dp; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  dinfo ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {char* d_name; int d_sectorsize; int d_mediasize; int /*<<< orphan*/  d_unit; int /*<<< orphan*/  d_maxsize; struct idad_softc* d_drv1; int /*<<< orphan*/  d_fwheads; int /*<<< orphan*/  d_fwsectors; int /*<<< orphan*/  d_dump; int /*<<< orphan*/  d_strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_LOG_DRV_INFO ; 
 int /*<<< orphan*/  DFLTPHYS ; 
 int /*<<< orphan*/  DISK_VERSION ; 
 int /*<<< orphan*/  DMA_DATA_IN ; 
 int ENXIO ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ida_command (struct ida_softc*,int /*<<< orphan*/ ,struct ida_drive_info*,int,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idad_dump ; 
 int /*<<< orphan*/  idad_strategy ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
idad_attach(device_t dev)
{
	struct ida_drive_info dinfo;
	struct idad_softc *drv;
	device_t parent;
	int error;

	drv = (struct idad_softc *)device_get_softc(dev);
	parent = device_get_parent(dev);
	drv->dev = dev;
	drv->controller = (struct ida_softc *)device_get_softc(parent);
	drv->unit = device_get_unit(dev);
	drv->drive = (intptr_t)device_get_ivars(dev);

	mtx_lock(&drv->controller->lock);
	error = ida_command(drv->controller, CMD_GET_LOG_DRV_INFO,
	    &dinfo, sizeof(dinfo), drv->drive, 0, DMA_DATA_IN);
	mtx_unlock(&drv->controller->lock);
	if (error) {
		device_printf(dev, "CMD_GET_LOG_DRV_INFO failed\n");
		return (ENXIO);
	}

	drv->cylinders = dinfo.dp.ncylinders;
	drv->heads = dinfo.dp.nheads;
	drv->sectors = dinfo.dp.nsectors;
	drv->secsize = dinfo.secsize == 0 ? 512 : dinfo.secsize;
	drv->secperunit = dinfo.secperunit;

	/* XXX
	 * other initialization
	 */
	device_printf(dev, "%uMB (%u sectors), blocksize=%d\n",
	    drv->secperunit / ((1024 * 1024) / drv->secsize),
	    drv->secperunit, drv->secsize);

	drv->disk = disk_alloc();
	drv->disk->d_strategy = idad_strategy;
	drv->disk->d_name = "idad";
	drv->disk->d_dump = idad_dump;
	drv->disk->d_sectorsize = drv->secsize;
	drv->disk->d_mediasize = (off_t)drv->secperunit * drv->secsize;
	drv->disk->d_fwsectors = drv->sectors;
	drv->disk->d_fwheads = drv->heads;
	drv->disk->d_drv1 = drv;
	drv->disk->d_maxsize = DFLTPHYS;		/* XXX guess? */
	drv->disk->d_unit = drv->unit;
	disk_create(drv->disk, DISK_VERSION);

	return (0);
}