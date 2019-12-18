#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_4__ {scalar_t__ busy; scalar_t__ state; struct TYPE_4__* parent; } ;

/* Variables and functions */
 scalar_t__ DS_ATTACHED ; 
 scalar_t__ DS_ATTACHING ; 
 scalar_t__ DS_BUSY ; 
 int /*<<< orphan*/  device_get_nameunit (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

void
device_unbusy(device_t dev)
{
	if (dev->busy != 0 && dev->state != DS_BUSY &&
	    dev->state != DS_ATTACHING)
		panic("device_unbusy: called for non-busy device %s",
		    device_get_nameunit(dev));
	dev->busy--;
	if (dev->busy == 0) {
		if (dev->parent)
			device_unbusy(dev->parent);
		if (dev->state == DS_BUSY)
			dev->state = DS_ATTACHED;
	}
}