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
struct lpt_data {int sc_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct lpt_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int HAVEBUS ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int ppb_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpt_request_ppbus(device_t dev, int how)
{
	device_t ppbus = device_get_parent(dev);
	struct lpt_data *sc = DEVTOSOFTC(dev);
	int error;

	/*
	 * We might already have the bus for a write(2) after an interrupted
	 * write(2) call.
	 */
	ppb_assert_locked(ppbus);
	if (sc->sc_state & HAVEBUS)
		return (0);

	error = ppb_request_bus(ppbus, dev, how);
	if (error == 0)
		sc->sc_state |= HAVEBUS;
	return (error);
}