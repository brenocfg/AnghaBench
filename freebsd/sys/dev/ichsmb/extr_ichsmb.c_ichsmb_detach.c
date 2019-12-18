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
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  smb; } ;

/* Variables and functions */
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichsmb_release_resources (TYPE_1__* const) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

int
ichsmb_detach(device_t dev)
{
	const sc_p sc = device_get_softc(dev);
	int error;

	error = bus_generic_detach(dev);
	if (error)
		return (error);
	device_delete_child(dev, sc->smb);
	ichsmb_release_resources(sc);
	mtx_destroy(&sc->mutex);
	
	return 0;
}