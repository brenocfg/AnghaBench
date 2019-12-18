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
struct TYPE_3__ {int poll; int /*<<< orphan*/  call_lock; } ;
typedef  TYPE_1__ ig4iic_softc_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IIC_EBUSBSY ; 
#define  IIC_RELEASE_BUS 129 
#define  IIC_REQUEST_BUS 128 
 int IIC_WAIT ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int errno2iic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_try_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

int
ig4iic_callback(device_t dev, int index, caddr_t data)
{
	ig4iic_softc_t *sc = device_get_softc(dev);
	int error = 0;
	int how;

	switch (index) {
	case IIC_REQUEST_BUS:
		/* force polling if ig4iic is requested with IIC_DONTWAIT */
		how = *(int *)data;
		if ((how & IIC_WAIT) == 0) {
			if (sx_try_xlock(&sc->call_lock) == 0)
				error = IIC_EBUSBSY;
			else
				sc->poll = true;
		} else
			sx_xlock(&sc->call_lock);
		break;

	case IIC_RELEASE_BUS:
		sc->poll = false;
		sx_unlock(&sc->call_lock);
		break;

	default:
		error = errno2iic(EINVAL);
	}

	return (error);
}