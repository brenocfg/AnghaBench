#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
typedef  TYPE_2__* devclass_t ;
struct TYPE_8__ {TYPE_1__** devices; } ;
struct TYPE_7__ {size_t unit; int flags; int /*<<< orphan*/ * nameunit; TYPE_2__* devclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCLANAME (TYPE_2__*) ; 
 int /*<<< orphan*/  DEVICENAME (TYPE_1__*) ; 
 int DF_WILDCARD ; 
 int /*<<< orphan*/  M_BUS ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
devclass_delete_device(devclass_t dc, device_t dev)
{
	if (!dc || !dev)
		return (0);

	PDEBUG(("%s in devclass %s", DEVICENAME(dev), DEVCLANAME(dc)));

	if (dev->devclass != dc || dc->devices[dev->unit] != dev)
		panic("devclass_delete_device: inconsistent device class");
	dc->devices[dev->unit] = NULL;
	if (dev->flags & DF_WILDCARD)
		dev->unit = -1;
	dev->devclass = NULL;
	free(dev->nameunit, M_BUS);
	dev->nameunit = NULL;

	return (0);
}