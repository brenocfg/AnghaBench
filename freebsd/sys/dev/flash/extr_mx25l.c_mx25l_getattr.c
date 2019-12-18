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
struct mx25l_softc {int /*<<< orphan*/  sc_dev; } ;
struct bio {int bio_length; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_attribute; TYPE_1__* bio_disk; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_2__ {struct mx25l_softc* d_drv1; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mx25l_getattr(struct bio *bp)
{
	struct mx25l_softc *sc;
	device_t dev;

	if (bp->bio_disk == NULL || bp->bio_disk->d_drv1 == NULL)
		return (ENXIO);

	sc = bp->bio_disk->d_drv1;
	dev = sc->sc_dev;

	if (strcmp(bp->bio_attribute, "SPI::device") == 0) {
		if (bp->bio_length != sizeof(dev))
			return (EFAULT);
		bcopy(&dev, bp->bio_data, sizeof(dev));
	} else
		return (-1);
	return (0);
}