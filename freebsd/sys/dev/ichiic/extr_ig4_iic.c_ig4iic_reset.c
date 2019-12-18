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
typedef  int u_char ;
struct TYPE_4__ {int last_slave; int slave_valid; int /*<<< orphan*/  call_lock; } ;
typedef  TYPE_1__ ig4iic_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_UNKNOWN ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_slave_addr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sx_xlocked (int /*<<< orphan*/ *) ; 

int
ig4iic_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	ig4iic_softc_t *sc = device_get_softc(dev);
	bool allocated;

	allocated = sx_xlocked(&sc->call_lock) != 0;
	if (!allocated)
		sx_xlock(&sc->call_lock);

	/* TODO handle speed configuration? */
	if (oldaddr != NULL)
		*oldaddr = sc->last_slave << 1;
	set_slave_addr(sc, addr >> 1);
	if (addr == IIC_UNKNOWN)
		sc->slave_valid = false;

	if (!allocated)
		sx_unlock(&sc->call_lock);
	return (0);
}