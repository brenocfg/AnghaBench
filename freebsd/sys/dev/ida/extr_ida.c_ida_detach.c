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
struct ida_softc {int /*<<< orphan*/  ida_dev_t; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (struct ida_softc*) ; 

int
ida_detach(device_t dev)
{
	struct ida_softc *ida;
	int error;

	ida = (struct ida_softc *)device_get_softc(dev);

	error = bus_generic_detach(dev);
	if (error)
		return (error);
	error = device_delete_children(dev);
	if (error)
		return (error);

	/*
	 * XXX
	 * before detaching, we must make sure that the system is
	 * quiescent; nothing mounted, no pending activity.
	 */

	/*
	 * XXX
	 * now, how are we supposed to maintain a list of our drives?
	 * iterate over our "child devices"?
	 */

	destroy_dev(ida->ida_dev_t);
	ida_free(ida);
	return (error);
}