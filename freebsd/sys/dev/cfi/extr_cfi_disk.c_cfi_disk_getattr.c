#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cfi_softc {int /*<<< orphan*/  sc_dev; } ;
struct cfi_disk_softc {struct cfi_softc* parent; } ;
struct bio {int bio_length; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_attribute; TYPE_1__* bio_disk; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_2__ {struct cfi_disk_softc* d_drv1; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cfi_disk_getattr(struct bio *bp)
{
	struct cfi_disk_softc *dsc;
	struct cfi_softc *sc;
	device_t dev;

	if (bp->bio_disk == NULL || bp->bio_disk->d_drv1 == NULL)
		return (ENXIO);

	dsc = bp->bio_disk->d_drv1;
	sc = dsc->parent;
	dev = sc->sc_dev;

	if (strcmp(bp->bio_attribute, "CFI::device") == 0) {
		if (bp->bio_length != sizeof(dev))
			return (EFAULT);
		bcopy(&dev, bp->bio_data, sizeof(dev));
	} else
		return (-1);
	return (0);
}