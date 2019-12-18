#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cam_eb {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

__attribute__((used)) static void
xpt_acquire_bus(struct cam_eb *bus)
{

	xpt_lock_buses();
	bus->refcount++;
	xpt_unlock_buses();
}