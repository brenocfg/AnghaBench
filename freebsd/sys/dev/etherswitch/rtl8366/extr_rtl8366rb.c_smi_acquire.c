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
struct rtl8366rb_softc {scalar_t__ smi_acquired; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  IIC_DONTWAIT ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int /*<<< orphan*/  RTL_LOCK (struct rtl8366rb_softc*) ; 
 scalar_t__ RTL_SMI_ACQUIRED ; 
 scalar_t__ RTL_TRYLOCK (struct rtl8366rb_softc*) ; 
 int /*<<< orphan*/  RTL_UNLOCK (struct rtl8366rb_softc*) ; 
 int RTL_WAITOK ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smi_acquire(struct rtl8366rb_softc *sc, int sleep)
{
	int r = 0;
	if (sleep == RTL_WAITOK)
		RTL_LOCK(sc);
	else
		if (RTL_TRYLOCK(sc) == 0)
			return (EWOULDBLOCK);
	if (sc->smi_acquired == RTL_SMI_ACQUIRED)
		r = EBUSY;
	else {
		r = iicbus_request_bus(device_get_parent(sc->dev), sc->dev, \
			sleep == RTL_WAITOK ? IIC_WAIT : IIC_DONTWAIT);
		if (r == 0)
			sc->smi_acquired = RTL_SMI_ACQUIRED;
	}
	RTL_UNLOCK(sc);
	return (r);
}