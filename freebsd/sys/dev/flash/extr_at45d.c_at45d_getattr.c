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
struct bio {int bio_length; int /*<<< orphan*/  bio_data; TYPE_1__* bio_disk; int /*<<< orphan*/  bio_attribute; } ;
struct at45d_softc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct at45d_softc* d_drv1; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
at45d_getattr(struct bio *bp)
{
	struct at45d_softc *sc;

	/*
	 * This function exists to support geom_flashmap and fdt_slicer.
	 */

	if (bp->bio_disk == NULL || bp->bio_disk->d_drv1 == NULL)
		return (ENXIO);
	if (strcmp(bp->bio_attribute, "SPI::device") != 0)
		return (-1);
	sc = bp->bio_disk->d_drv1;
	if (bp->bio_length != sizeof(sc->dev))
		return (EFAULT);
	bcopy(&sc->dev, bp->bio_data, sizeof(sc->dev));
	return (0);
}