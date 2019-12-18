#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* device_t ;
struct TYPE_7__ {TYPE_2__* dev_module; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {char const* name; } ;

/* Variables and functions */
 char const* unknown_string ; 

const char *
device_get_name(device_t dev)
{
	if (dev == NULL)
		return (unknown_string);

	return (dev->dev_module->driver->name);
}