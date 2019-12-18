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
typedef  TYPE_1__* device_t ;
struct TYPE_3__ {scalar_t__ dev_softc_alloc; int /*<<< orphan*/ * dev_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
device_set_softc(device_t dev, void *softc)
{
	if (dev->dev_softc_alloc) {
		free(dev->dev_sc, M_DEVBUF);
		dev->dev_sc = NULL;
	}
	dev->dev_sc = softc;
	dev->dev_softc_alloc = 0;
}