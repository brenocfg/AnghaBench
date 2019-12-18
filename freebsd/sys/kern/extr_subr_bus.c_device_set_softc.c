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
struct TYPE_3__ {int flags; void* softc; } ;

/* Variables and functions */
 int DF_EXTERNALSOFTC ; 
 int /*<<< orphan*/  M_BUS_SC ; 
 int /*<<< orphan*/  free_domain (void*,int /*<<< orphan*/ ) ; 

void
device_set_softc(device_t dev, void *softc)
{
	if (dev->softc && !(dev->flags & DF_EXTERNALSOFTC))
		free_domain(dev->softc, M_BUS_SC);
	dev->softc = softc;
	if (dev->softc)
		dev->flags |= DF_EXTERNALSOFTC;
	else
		dev->flags &= ~DF_EXTERNALSOFTC;
}