#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICENAME (TYPE_1__*) ; 
 int DEVICE_QUIESCE (TYPE_1__*) ; 
 scalar_t__ DS_ATTACHED ; 
 scalar_t__ DS_BUSY ; 
 int EBUSY ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 

int
device_quiesce(device_t dev)
{

	PDEBUG(("%s", DEVICENAME(dev)));
	if (dev->state == DS_BUSY)
		return (EBUSY);
	if (dev->state != DS_ATTACHED)
		return (0);

	return (DEVICE_QUIESCE(dev));
}