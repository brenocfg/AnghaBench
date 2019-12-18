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
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int DF_QUIET_CHILDREN ; 

int
device_has_quiet_children(device_t dev)
{
	return ((dev->flags & DF_QUIET_CHILDREN) != 0);
}