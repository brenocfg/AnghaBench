#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
typedef  TYPE_2__* devclass_t ;
struct TYPE_10__ {char* name; TYPE_1__** devices; } ;
struct TYPE_9__ {size_t unit; int /*<<< orphan*/ * nameunit; TYPE_2__* devclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCLANAME (TYPE_2__*) ; 
 int /*<<< orphan*/  DEVICENAME (TYPE_1__*) ; 
 int ENOMEM ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  M_BUS ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int devclass_alloc_unit (TYPE_2__*,TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int snprintf (int /*<<< orphan*/ *,int,char*,char*,size_t) ; 

__attribute__((used)) static int
devclass_add_device(devclass_t dc, device_t dev)
{
	int buflen, error;

	PDEBUG(("%s in devclass %s", DEVICENAME(dev), DEVCLANAME(dc)));

	buflen = snprintf(NULL, 0, "%s%d$", dc->name, INT_MAX);
	if (buflen < 0)
		return (ENOMEM);
	dev->nameunit = malloc(buflen, M_BUS, M_NOWAIT|M_ZERO);
	if (!dev->nameunit)
		return (ENOMEM);

	if ((error = devclass_alloc_unit(dc, dev, &dev->unit)) != 0) {
		free(dev->nameunit, M_BUS);
		dev->nameunit = NULL;
		return (error);
	}
	dc->devices[dev->unit] = dev;
	dev->devclass = dc;
	snprintf(dev->nameunit, buflen, "%s%d", dc->name, dev->unit);

	return (0);
}