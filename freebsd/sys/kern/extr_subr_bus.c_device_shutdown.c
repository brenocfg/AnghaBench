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
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int DEVICE_SHUTDOWN (TYPE_1__*) ; 
 scalar_t__ DS_ATTACHED ; 

int
device_shutdown(device_t dev)
{
	if (dev->state < DS_ATTACHED)
		return (0);
	return (DEVICE_SHUTDOWN(dev));
}