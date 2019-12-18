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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DF_FIXEDCLASS ; 
 int EINVAL ; 
 int device_set_devclass (TYPE_1__*,char const*) ; 

int
device_set_devclass_fixed(device_t dev, const char *classname)
{
	int error;

	if (classname == NULL)
		return (EINVAL);

	error = device_set_devclass(dev, classname);
	if (error)
		return (error);
	dev->flags |= DF_FIXEDCLASS;
	return (0);
}