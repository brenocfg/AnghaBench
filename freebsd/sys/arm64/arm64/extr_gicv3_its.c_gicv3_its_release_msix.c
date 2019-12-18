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
struct TYPE_2__ {scalar_t__ lpi_busy; } ;
struct its_dev {TYPE_1__ lpis; } ;
struct intr_irqsrc {int dummy; } ;
struct gicv3_its_irqsrc {int /*<<< orphan*/ * gi_its_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct its_dev* its_device_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_device_release (int /*<<< orphan*/ ,struct its_dev*) ; 

__attribute__((used)) static int
gicv3_its_release_msix(device_t dev, device_t child, struct intr_irqsrc *isrc)
{
	struct gicv3_its_irqsrc *girq;
	struct its_dev *its_dev;

	its_dev = its_device_find(dev, child);

	KASSERT(its_dev != NULL,
	    ("gicv3_its_release_msix: Releasing a MSI-X interrupt with "
	     "no ITS device"));
	KASSERT(its_dev->lpis.lpi_busy > 0,
	    ("gicv3_its_release_msix: Releasing more interrupts than "
	     "were allocated: allocated %d", its_dev->lpis.lpi_busy));
	girq = (struct gicv3_its_irqsrc *)isrc;
	girq->gi_its_dev = NULL;
	its_dev->lpis.lpi_busy--;

	if (its_dev->lpis.lpi_busy == 0)
		its_device_release(dev, its_dev);

	return (0);
}