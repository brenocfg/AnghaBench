#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct gpiokeys_softc {int dummy; } ;
struct TYPE_5__ {struct gpiokeys_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {scalar_t__ td_critnest; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  GPIOKEYS_LOCK (struct gpiokeys_softc*) ; 
 int /*<<< orphan*/  GPIOKEYS_UNLOCK (struct gpiokeys_softc*) ; 
 TYPE_4__* curthread ; 
 int gpiokeys_ioctl_locked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiokeys_ioctl(keyboard_t *kbd, u_long cmd, caddr_t arg)
{
	int result;
	struct gpiokeys_softc *sc;

	sc = kbd->kb_data;
	/*
	 * XXX Check if someone is calling us from a critical section:
	 */
	if (curthread->td_critnest != 0)
		return (EDEADLK);

	GPIOKEYS_LOCK(sc);
	result = gpiokeys_ioctl_locked(kbd, cmd, arg);
	GPIOKEYS_UNLOCK(sc);

	return (result);
}